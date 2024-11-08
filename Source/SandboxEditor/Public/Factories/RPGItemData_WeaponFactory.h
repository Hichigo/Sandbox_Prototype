// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "RPGItemData_WeaponFactory.generated.h"

/**
 *
 */
UCLASS()

class SANDBOXEDITOR_API URPGItemData_WeaponFactory : public UFactory
{
    GENERATED_BODY()
public:
    URPGItemData_WeaponFactory(const FObjectInitializer& ObjectInitializer);

    virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
