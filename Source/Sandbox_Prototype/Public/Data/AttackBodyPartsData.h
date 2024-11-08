// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttackBodyPartsData.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SANDBOX_PROTOTYPE_API UAttackBodyPartsData : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Body part")
    TMap<FName, FGameplayTag> AttackBodyPart;
};
