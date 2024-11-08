// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ItemCore.h"
#include "Types/ItemTypes.h"
#include "WeaponCore.generated.h"

UCLASS(Abstract, BlueprintType)
class SANDBOX_PROTOTYPE_API AWeaponCore : public AItemCore
{
    GENERATED_BODY()

public:
    AWeaponCore(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, Category = "RPG|Weapon")
    virtual void BeginAttack();

    UFUNCTION(BlueprintCallable, Category = "RPG|Weapon")
    virtual void EndAttack();

    void SetWeaponInfo(const FWeaponInfo& InWeaponInfo);

    UFUNCTION(BlueprintPure, Category = "RPG|Weapon")
    FWeaponInfo GetWeaponInfo() const;

    UFUNCTION(BlueprintPure, Category = "RPG|Weapon")
    bool IsAttacking() const;

    UFUNCTION(BlueprintPure, Category = "RPG|Creature")
    virtual USkeletalMeshComponent* GetWeaponSkeletalMesh() const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "RPG|Weapon")
    FWeaponInfo WeaponInfo;

    bool bAttacking;
};
