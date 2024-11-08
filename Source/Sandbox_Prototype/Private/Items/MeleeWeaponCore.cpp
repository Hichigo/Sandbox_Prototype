// Copyright Nexus Studio. All Rights Reserved.

#include "Items/MeleeWeaponCore.h"
#include "KismetTraceUtils.h"
#include "Interfaces/DamageInterface.h"
#include "Types/RPGTypes.h"

AMeleeWeaponCore::AMeleeWeaponCore(const FObjectInitializer& ObjectInitializer)  //
    : Super(ObjectInitializer),                                                  //
      BoxSizeAttack(FVector(38.0f, 4.0f, 2.0f)),                                 //
      TraceAttackSocketName("TraceAttack_01")                                    //
{
    PrimaryActorTick.bCanEverTick = true;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
    RootComponent = WeaponMesh;

    AttackObjectsType.Add(GCreature_Object);
}

void AMeleeWeaponCore::BeginAttack()
{
    bAttacking = true;
    SetActorTickEnabled(true);
    PrevLocation = WeaponMesh->GetSocketLocation(TraceAttackSocketName);
    IgnoreActors.Reset();
}

void AMeleeWeaponCore::EndAttack()
{
    bAttacking = false;
    SetActorTickEnabled(false);
}
USkeletalMeshComponent* AMeleeWeaponCore::GetWeaponSkeletalMesh() const
{
    return WeaponMesh;
}

void AMeleeWeaponCore::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    Attack();
}

void AMeleeWeaponCore::Attack()
{
    FTransform TraceAttackSocketTransform = WeaponMesh->GetSocketTransform(TraceAttackSocketName);

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);
    QueryParams.AddIgnoredActor(Owner);  // Owner pointer
    QueryParams.AddIgnoredActors(IgnoreActors);
    QueryParams.bTraceComplex = true;
    QueryParams.bReturnPhysicalMaterial = true;

    FHitResult Hit;

    const bool bResultTrace = GetWorld()->SweepSingleByObjectType(  //
        Hit,                                                        //
        PrevLocation,                                               //
        TraceAttackSocketTransform.GetLocation(),                   //
        TraceAttackSocketTransform.GetRotation(),                   //
        ObjectQueryParams,                                          //
        FCollisionShape::MakeBox(BoxSizeAttack),                    //
        QueryParams                                                 //
    );

    PrevLocation = TraceAttackSocketTransform.GetLocation();

    if (bResultTrace)
    {
        AActor* HitActor = Hit.GetActor();
        auto* DamageInterface = Cast<IDamageInterface>(HitActor);
        if (DamageInterface)
        {
            DamageInfo.Damage = WeaponInfo.Damage;
            DamageInfo.HitBone = Hit.BoneName;
            DamageInterface->Execute_ReceiveDamage(HitActor, DamageInfo);
            IgnoreActors.Add(HitActor);
        }
    }

    if (bShowTrace)
    {
        DrawDebugBoxTraceSingle(                                 //
            GetWorld(),                                          //
            PrevLocation,                                        //
            TraceAttackSocketTransform.GetLocation(),            //
            BoxSizeAttack,                                       //
            TraceAttackSocketTransform.GetRotation().Rotator(),  //
            EDrawDebugTrace::ForDuration,                        //
            bResultTrace,                                        //
            Hit,                                                 //
            FColor::Red,                                         //
            FColor::Green,                                       //
            bResultTrace ? 10.0f : 5.0f                          //
        );
        /*DrawDebugBox(                                    //
            GetWorld(),                                  //
            TraceAttackSocketTransform.GetLocation(),    //
            BoxSizeAttack,                               //
            TraceAttackSocketTransform.GetRotation(),    //
            bResultTrace ? FColor::Green : FColor::Red,  //
            false,                                       //
            3.0f,                                        //
            0,                                           //
            1                                            //
        );*/
    }
}

void AMeleeWeaponCore::BeginPlay()
{
    Super::BeginPlay();

    SetActorTickEnabled(false);

    DamageInfo.DamageCauser = GetOwner();
    DamageInfo.DamageTypeTag = DamageTypeTag;

    for (auto& ObjectType : AttackObjectsType)
    {
        ObjectQueryParams.AddObjectTypesToQuery(ObjectType);
    }
}
