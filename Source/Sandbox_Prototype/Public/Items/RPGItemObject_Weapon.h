// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RPGItemObject.h"
#include "RPGItemObject_Weapon.generated.h"

UCLASS(BlueprintType)
class SANDBOX_PROTOTYPE_API URPGItemObject_Weapon : public URPGItemObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", Meta = (ExposeOnSpawn = true))
    FWeaponInfo WeaponInfo;
};
