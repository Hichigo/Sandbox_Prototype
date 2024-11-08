// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types/ItemTypes.h"
#include "UObject/Object.h"
#include "RPGItemObject.generated.h"

UCLASS(BlueprintType)

class SANDBOX_PROTOTYPE_API URPGItemObject : public UObject
{
    GENERATED_BODY()

public:
    URPGItemObject() : Amount(1) {}

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", Meta = (ExposeOnSpawn = true))
    FRPGItemInfo CommonData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", Meta = (ExposeOnSpawn = true))
    int32 Amount;

    UFUNCTION(BlueprintCallable, Category = "RPG|Item")
    bool IsStackable() const;

    int32 AddToStack(int32 InAmount);

    bool IsNotFullStack() const { return Amount < CommonData.UIData.MaxAmountInStack; }
};
