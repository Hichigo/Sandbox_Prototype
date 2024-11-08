// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemCore.generated.h"

UCLASS(Abstract, BlueprintType)
class SANDBOX_PROTOTYPE_API AItemCore : public AActor
{
    GENERATED_BODY()

public:
    AItemCore(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void BeginPlay() override;
};
