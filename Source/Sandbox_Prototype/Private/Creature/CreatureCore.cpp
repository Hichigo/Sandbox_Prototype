// Copyright Nexus Studio. All Rights Reserved.

#include "Creature/CreatureCore.h"
#include "AIController.h"
#include "Components/AttributesComponent.h"
#include "Components/BodyComponent.h"
#include "Components/EquipmentComponent.h"
#include "Components/InventoryComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/AIHelperInterface.h"
#include "Items/RPGItemObject_Weapon.h"
#include "Items/WeaponCore.h"
#include "Other/RPGHelperFunctionLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogACreatureCore, All, All);

ACreatureCore::ACreatureCore(const FObjectInitializer& ObjectInitializer)  //
    : Super(ObjectInitializer),                                            //
      bDeath(false),                                                       //
      bUnconscious(false),                                                 //
      UnconsciousTime(30.0f),                                              //
      DelayBetweenAttack(2.0f),                                            //
      LastTimeAttack(0.0f),                                                //
      ParryChance(25),                                                     //
      DodgeChance(10),                                                     //
      HitReactionChance(20),                                               //
      Team(ETeam::None)                                                    //
{
    PrimaryActorTick.bCanEverTick = false;

    InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

    EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("Equipment"));

    AttributesComponent = CreateDefaultSubobject<UAttributesComponent>(TEXT("Attributes"));

    BodyComponent = CreateDefaultSubobject<UBodyComponent>(TEXT("Body"));

    GetMesh()->SetCustomDepthStencilValue(252);
}

void ACreatureCore::SetNewActionTag_Implementation(const FGameplayTag& InActionTag)
{
    ActionTag = InActionTag;

    if (ActionTag.MatchesTagExact(FightActionTag))
    {
        GetCharacterMovement()->bOrientRotationToMovement = false;
    }
    else
    {
        GetCharacterMovement()->bOrientRotationToMovement = true;
    }
}

FGameplayTag ACreatureCore::GetActionTag_Implementation()
{
    return ActionTag;
}

AWeaponCore* ACreatureCore::GetPrimaryWeapon_Implementation()
{
    return PrimaryWeapon;
}

void ACreatureCore::SetPrimaryWeapon_Implementation(AWeaponCore* InWeapon)
{
    PrimaryWeapon = InWeapon;
}

ETeam ACreatureCore::GetTeam_Implementation()
{
    return Team;
}

FOnUpdateConsciousDelegate& ACreatureCore::GetUpdateConsciousDelegate()
{
    return OnUpdateConsciousDelegate;
}

void ACreatureCore::ReceiveDamage_Implementation(const FDamageInfo& InDamageInfo)
{
    if (ParryCauser && ParryCauser == InDamageInfo.DamageCauser)
    {
        ClearParryCauser();
        return;
    }

    if (URPGHelperFunctionLibrary::IsEnemyTeam(Team, InDamageInfo.DamageCauser))
    {
        OnTakeDamageDelegate.Broadcast(InDamageInfo.DamageCauser, InDamageInfo.Damage);

        // TODO: here calculate resists and defence???

        BodyComponent->MakeDamage(InDamageInfo.Damage, InDamageInfo.HitBone, InDamageInfo.DamageTypeTag);

        if (CanPlayMontage())
        {
            const float Chance = FMath::RandHelper(100);
            if (Chance < HitReactionChance)
            {
                const FVector DirectionToCauser = (InDamageInfo.DamageCauser->GetActorLocation() - GetActorLocation()).GetSafeNormal2D();

                FName SectionName = "Forward";
                const float CheckRightSide = GetActorRightVector().GetSafeNormal2D().Dot(DirectionToCauser);
                const float CheckForwardSide = GetActorForwardVector().GetSafeNormal2D().Dot(DirectionToCauser);

                if (CheckRightSide >= 0.5f)
                {
                    SectionName = "Right";
                }
                else if (CheckRightSide <= -0.5f)
                {
                    SectionName = "Left";
                }
                else if (CheckForwardSide <= -0.5f)
                {
                    SectionName = "Back";
                    return;  // TODO: add hit reaction animation for attack to behind
                }

                const float HitReactionDuration = PlayAnimMontage(HitReactionMontage, 1.0f, SectionName);

                LastTimeAttack = GetWorld()->GetTimeSeconds() + HitReactionDuration;
            }
        }
    }
}

void ACreatureCore::PrepareReceiveDamage_Implementation(AActor* InDamageCauser)
{
    check(InDamageCauser);
    if (CanPlayMontage() == false)
    {
        return;
    }

    const FVector DirectionToCauser = (InDamageCauser->GetActorLocation() - GetActorLocation()).GetSafeNormal2D();
    if (GetActorForwardVector().Dot(DirectionToCauser) >= 0.5f)
    {
        // check can dodge
        float Chance = FMath::FRandRange(0.0f, 100.0f);  // RandHelper(100);

        if (Chance < DodgeChance)
        {
            PlayAnimMontage(DodgeMontage);
            return;
        }

        // check can parry
        Chance = FMath::RandHelper(100);
        if (Chance < ParryChance)
        {
            const FGameplayTag AttackDirectionTag = Execute_GetAttackDirection(InDamageCauser);
            const FName* SectionName = DirectionsSectionName.Find(AttackDirectionTag);
            if (SectionName)
            {
                PlayAnimMontage(ParryMontage, 1.0f, *SectionName);
            }
            else
            {
                PlayAnimMontage(ParryMontage, 1.0f, "Forward");
            }

            ParryCauser = InDamageCauser;
        }
    }
}

void ACreatureCore::BeginAttack_Implementation()
{
    if (PrimaryWeapon)
    {
        PrimaryWeapon->BeginAttack();
        IAIHelperInterface::Execute_WarnAttack(GetController());
    }
}

void ACreatureCore::EndAttack_Implementation()
{
    if (PrimaryWeapon)
    {
        PrimaryWeapon->EndAttack();
    }
}

FGameplayTag ACreatureCore::GetAttackDirection_Implementation()
{
    return CurrentAttackDirectionTag;
}

bool ACreatureCore::IsConscious_Implementation() const
{
    return !bUnconscious;
}

bool ACreatureCore::IsAlive_Implementation() const
{
    return !bDeath;
}

FOnTakeDamageDelegate& ACreatureCore::GetTakeDamageDelegate()
{
    return OnTakeDamageDelegate;
}

void ACreatureCore::Click_Implementation(AAIController* InAIController)
{
    const auto* AIHelperInterface = Cast<IAIHelperInterface>(InAIController);
    if (AIHelperInterface)
    {
        AIHelperInterface->Execute_SetOpponent(InAIController, this);
    }
}

void ACreatureCore::NotifyActorBeginCursorOver()
{
    GetMesh()->SetRenderCustomDepth(true);
}

void ACreatureCore::NotifyActorEndCursorOver()
{
    GetMesh()->SetRenderCustomDepth(false);
}

void ACreatureCore::GetActorEyesViewPoint(FVector& Location, FRotator& Rotation) const
{
    Location = GetMesh()->GetBoneLocation("head");
    Rotation = GetActorRotation();
}

float ACreatureCore::Attack()
{
    UAnimMontage* AttackMontage = GetAttackAnim();

    const float AnimationLength = PlayAnimMontage(AttackMontage);

    // last time attack calculated after end animation
    LastTimeAttack = GetWorld()->GetTimeSeconds() + AnimationLength;

    return AnimationLength;
}

float ACreatureCore::GetCurrentMontageDuration() const
{
    const UAnimMontage* CurrentMontage = GetCurrentMontage();
    if (CurrentMontage)
    {
        return CurrentMontage->GetPlayLength();
    }

    return 0.0f;
}

void ACreatureCore::AddAttackDirectionTag(const FGameplayTag& InDirectionTag)
{
    AttackDirectionsTag.AddTag(InDirectionTag);
}

void ACreatureCore::RemoveAttackDirectionTag(const FGameplayTag& InDirectionTag)
{
    AttackDirectionsTag.RemoveTag(InDirectionTag);
}

void ACreatureCore::ClearParryCauser()
{
    ParryCauser = nullptr;
}

void ACreatureCore::BeginPlay()
{
    Super::BeginPlay();

    // GetMesh()->SetCollisionProfileName("Hittable");

    UpdateAnimationLayer(DefaultAnimationLayerClass);

    BodyComponent->OnUnconsciousDelegate.AddDynamic(this, &ThisClass::UnconsciousHandle);
    BodyComponent->OnLostBodyPartDelegate.AddDynamic(this, &ThisClass::LostBodyPartHandle);
    BodyComponent->OnDeathDelegate.AddDynamic(this, &ThisClass::DeathHandle);

    EquipmentComponent->OnEquipmentUpdatedDelegate.AddDynamic(this, &ThisClass::EquipItemHandle);
}

bool ACreatureCore::CanPlayMontage() const
{
    if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying())
    {
        FAnimMontageInstance* CurrentMontage = GetMesh()->GetAnimInstance()->GetActiveMontageInstance();
        if (CurrentMontage)
        {
            const float TimeRemainingPercent = CurrentMontage->Montage->GetPlayLength() - CurrentMontage->GetPosition();
            if (TimeRemainingPercent > 0.2f)
            {
                return false;
            }
        }
    }

    return true;
}

void ACreatureCore::UpdateAnimationLayer(const TSubclassOf<UAnimInstance>& InAnimationLayerClass)
{
    CurrentAnimationLayerClass = InAnimationLayerClass;
    GetMesh()->LinkAnimClassLayers(CurrentAnimationLayerClass);
}

void ACreatureCore::UnconsciousHandle()
{
    bUnconscious = true;
    OnUpdateConsciousDelegate.Broadcast(bUnconscious);

    GetWorldTimerManager().SetTimer(  //
        ConsciousTimerHandle,         //
        this,                         //
        &ThisClass::ConsciousHandle,  //
        UnconsciousTime,              //
        false                         //
    );
}

void ACreatureCore::ConsciousHandle()
{
    bUnconscious = false;
}

void ACreatureCore::UpdateConsciousBroadcast()
{
    OnUpdateConsciousDelegate.Broadcast(bUnconscious);
}

void ACreatureCore::LostBodyPartHandle(const FGameplayTag& InLostBodyPartTag)
{
    // TODO: logic lost body part
    // if (const FName* BrokenBodyPart = CanBrokenBodyParts.Find(LostBodyPartTag))
    // {
    //     GetMesh()->SetAllBodiesBelowSimulatePhysics(*BrokenBodyPart, true);
    // }
}

void ACreatureCore::DeathHandle()
{
    // TODO: Death logic
    bDeath = true;
    GetMesh()->SetCollisionProfileName("Ragdoll");
    GetMesh()->SetAllBodiesSimulatePhysics(true);
    GetMesh()->SetSimulatePhysics(true);
}

void ACreatureCore::EquipItemHandle(const bool bIsEquiped, URPGItemObject* EquipItemObject)
{
    // TODO: this function need refactoring
    if (bIsEquiped)
    {
        if (EquipItemObject->CommonData.Type == FPrimaryAssetType("Weapon"))
        {
            auto* ItemObject_Weapon = Cast<URPGItemObject_Weapon>(EquipItemObject);
            if (ItemObject_Weapon)
            {
                FActorSpawnParameters SpawnParameters;
                SpawnParameters.Owner = this;
                SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

                PrimaryWeapon = GetWorld()->SpawnActor<AWeaponCore>(ItemObject_Weapon->WeaponInfo.WeaponClass, SpawnParameters);

                if (PrimaryWeapon)
                {
                    PrimaryWeapon->AttachToComponent(                              //
                        GetMesh(),                                                 //
                        FAttachmentTransformRules::SnapToTargetNotIncludingScale,  //
                        "HandR_Weapon"                                             //
                    );

                    PrimaryWeapon->SetWeaponInfo(ItemObject_Weapon->WeaponInfo);

                    UpdateAnimationLayer(ItemObject_Weapon->WeaponInfo.AnimLayerClass);
                }
            }
        }
    }
    else
    {
        if (EquipItemObject->CommonData.Type == FPrimaryAssetType("Weapon"))
        {
            PrimaryWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
            PrimaryWeapon->Destroy();

            UpdateAnimationLayer(DefaultAnimationLayerClass);
        }
    }
}

UAnimMontage* ACreatureCore::GetAttackAnim()
{
    FAnimDirections CurrentLayerAttackAnims = *AttackAnimationsByLayers.Find(CurrentAnimationLayerClass);

    if (AttackDirectionsTag.Num() == 0)
    {
        TArray<FGameplayTag> DirectionTags;
        CurrentLayerAttackAnims.AttackAnimations.GetKeys(DirectionTags);

        const int32 RandomIndex = FMath::RandHelper(DirectionTags.Num());
        CurrentAttackDirectionTag = DirectionTags[RandomIndex];

        return CurrentLayerAttackAnims.AttackAnimations[CurrentAttackDirectionTag];
    }

    const int32 RandomIndex = FMath::RandHelper(AttackDirectionsTag.Num());
    CurrentAttackDirectionTag = AttackDirectionsTag.GetByIndex(RandomIndex);

    return CurrentLayerAttackAnims.AttackAnimations[CurrentAttackDirectionTag];
}
