// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayInterface.generated.h"

class AAIController;
UINTERFACE(BlueprintType)

class UGameplayInterface : public UInterface
{
    GENERATED_BODY()
};

class SANDBOX_PROTOTYPE_API IGameplayInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Gameplay")
    void Click(AAIController* InAIController);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Gameplay")
    bool Interact(AActor* InActor);
};
