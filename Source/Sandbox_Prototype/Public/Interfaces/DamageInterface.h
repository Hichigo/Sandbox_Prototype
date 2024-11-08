// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Types/DamageTypes.h"
#include "UObject/Interface.h"
#include "DamageInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTakeDamageDelegate, AActor*, DamageCauser, const float, Damage);

UINTERFACE(BlueprintType)
class UDamageInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class SANDBOX_PROTOTYPE_API IDamageInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Damage")
    void ReceiveDamage(const FDamageInfo& InDamageInfo);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Damage")
    void PrepareReceiveDamage(AActor* InDamageCauser);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Damage")
    void BeginAttack();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Damage")
    void EndAttack();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Damage")
    FGameplayTag GetAttackDirection();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Creature")
    bool IsConscious() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Creature")
    bool IsAlive() const;

    // UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Creature")
    virtual FOnTakeDamageDelegate& GetTakeDamageDelegate() = 0;
};
