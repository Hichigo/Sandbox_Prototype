// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AttributeTypes.generated.h"

USTRUCT(BlueprintType)
struct FBar
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG")
    float Current;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG")
    float Max;

    FBar()
    {
        Current = 100.0f;
        Max = 100.0f;
    }

    FBar(const float InCurrent, const float InMax)
    {
        Current = InCurrent;
        Max = InMax;
    }
};

USTRUCT(BlueprintType)
struct FBodyPart
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body part")
    FText Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body part")
    FGameplayTag Tag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body part")
    FBar Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body part")
    FBar HiddenHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body part")
    bool bLost;

    FBodyPart()
    {
        Name = FText::FromString("{Name}");
        bLost = false;
    }
};

USTRUCT(BlueprintType)
struct FAttribute
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
    FText Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
    FName TableRowName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
    int32 Value;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
    FGameplayTag TypeTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
    FGameplayTag ModeTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
    FBar Exp;

    FAttribute()
    {
        Name = FText::FromString("{AttributeName}");
        TableRowName = "{TableRowName}";
        Value = 1;
        Exp = FBar(0.0f, 100.0f);
    }
};