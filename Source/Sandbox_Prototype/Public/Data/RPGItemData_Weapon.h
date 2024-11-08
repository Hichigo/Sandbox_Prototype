// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RPGItemData.h"
#include "RPGItemData_Weapon.generated.h"

UCLASS()
class SANDBOX_PROTOTYPE_API URPGItemData_Weapon : public URPGItemData
{
    GENERATED_BODY()

public:
    URPGItemData_Weapon();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    FWeaponInfo WeaponInfo;
};
