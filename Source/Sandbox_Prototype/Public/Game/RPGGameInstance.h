// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RPGGameInstance.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SANDBOX_PROTOTYPE_API URPGGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    URPGGameInstance(const FObjectInitializer& ObjectInitializer);
};
