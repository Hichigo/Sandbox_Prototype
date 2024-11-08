// Copyright Nexus Studio. All Rights Reserved.

#include "Items/WeaponCore.h"

AWeaponCore::AWeaponCore(const FObjectInitializer& ObjectInitializer)  //
    : Super(ObjectInitializer),                                        //
      bAttacking(false)                                                //
{
    PrimaryActorTick.bCanEverTick = false;
}

void AWeaponCore::BeginAttack() {}

void AWeaponCore::EndAttack() {}

void AWeaponCore::SetWeaponInfo(const FWeaponInfo& InWeaponInfo)
{
    WeaponInfo = InWeaponInfo;
}

FWeaponInfo AWeaponCore::GetWeaponInfo() const
{
    return WeaponInfo;
}

bool AWeaponCore::IsAttacking() const
{
    return bAttacking;
}

USkeletalMeshComponent* AWeaponCore::GetWeaponSkeletalMesh() const
{
    return nullptr;
}
