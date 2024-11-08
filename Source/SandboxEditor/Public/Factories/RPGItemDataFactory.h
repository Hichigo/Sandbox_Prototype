// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Factories/Factory.h"
#include "RPGItemDataFactory.generated.h"

/**
 *
 */
UCLASS()

class SANDBOXEDITOR_API URPGItemDataFactory : public UFactory
{
    GENERATED_BODY()

public:
    URPGItemDataFactory(const FObjectInitializer& ObjectInitializer);

    virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
