// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Types/CreatureTypes.h"
#include "UObject/Interface.h"
#include "CreatureInterface.generated.h"

class AWeaponCore;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateConsciousDelegate, bool, bIsUnconscious);

UINTERFACE(BlueprintType)
class UCreatureInterface : public UInterface
{
    GENERATED_BODY()
};

class SANDBOX_PROTOTYPE_API ICreatureInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Creature")
    void SetNewActionTag(const FGameplayTag& InActionTag);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Creature")
    FGameplayTag GetActionTag();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Creature")
    AWeaponCore* GetPrimaryWeapon();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Creature")
    void SetPrimaryWeapon(AWeaponCore* InWeapon);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Creature")
    ETeam GetTeam();

    virtual FOnUpdateConsciousDelegate& GetUpdateConsciousDelegate() = 0;
};
