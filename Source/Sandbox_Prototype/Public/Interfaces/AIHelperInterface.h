// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AIHelperInterface.generated.h"

UINTERFACE(BlueprintType)

class UAIHelperInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class SANDBOX_PROTOTYPE_API IAIHelperInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|AI")
    void SetTargetLocation(const FVector& InLocation);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|AI")
    void AddTargetLocation(const FVector& InLocation);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|AI")
    void SetOpponent(AActor* InActor);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|AI")
    void SetInteractActor(AActor* InActor);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|AI")
    void SetAINewActionTag(const FGameplayTag& InActionTag);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|AI")
    void WarnAttack();
};
