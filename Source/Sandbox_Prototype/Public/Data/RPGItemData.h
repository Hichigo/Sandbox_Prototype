// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Types/ItemTypes.h"
#include "RPGItemData.generated.h"

UCLASS(BlueprintType)
class SANDBOX_PROTOTYPE_API URPGItemData : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    URPGItemData();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    FRPGItemInfo CommonData;

    UFUNCTION(BlueprintCallable, Category = "RPG|Item")
    FString GetIdentifierString() const;

    UFUNCTION(BlueprintCallable, Category = "RPG|Item")
    virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
