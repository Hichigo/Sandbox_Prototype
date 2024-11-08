// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "WeaponCore.h"
#include "Types/DamageTypes.h"
#include "MeleeWeaponCore.generated.h"

UCLASS(Abstract, BlueprintType)
class SANDBOX_PROTOTYPE_API AMeleeWeaponCore : public AWeaponCore
{
    GENERATED_BODY()

public:
    AMeleeWeaponCore(const FObjectInitializer& ObjectInitializer);

    virtual void BeginAttack() override;

    virtual void EndAttack() override;

    virtual USkeletalMeshComponent* GetWeaponSkeletalMesh() const override;

    virtual void Tick(float DeltaTime) override;

protected:
    FVector PrevLocation;

    FDamageInfo DamageInfo;

    UPROPERTY()
    TArray<AActor*> IgnoreActors;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Item")
    FGameplayTag DamageTypeTag;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Item")
    FVector BoxSizeAttack;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Item")
    FName TraceAttackSocketName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Item")
    TArray<TEnumAsByte<ECollisionChannel>> AttackObjectsType;

    FCollisionObjectQueryParams ObjectQueryParams;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Debug")
    bool bShowTrace;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Item")
    TObjectPtr<USkeletalMeshComponent> WeaponMesh;

    void Attack();

    virtual void BeginPlay() override;
};
