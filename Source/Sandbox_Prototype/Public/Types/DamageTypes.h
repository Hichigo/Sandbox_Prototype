// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DamageTypes.generated.h"

USTRUCT(BlueprintType)
struct FDamageInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    float Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    FName HitBone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    FGameplayTag DamageTypeTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    AActor* DamageCauser;

    FDamageInfo()
    {
        Damage = 0.0f;
        HitBone = NAME_None;
        DamageCauser = nullptr;
    }
};