// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class URPGItemObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdatedDelegate);

UCLASS(Blueprintable, ClassGroup = (RPG), meta = (BlueprintSpawnableComponent))

class SANDBOX_PROTOTYPE_API UInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UInventoryComponent(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintPure, Category = "RPG|Inventory")
    TMap<URPGItemObject*, FIntPoint> GetAllItems() const;

    UFUNCTION(BlueprintCallable, Category = "RPG|Inventory")
    void RemoveItem(const URPGItemObject* Item);

    UFUNCTION(BlueprintCallable, Category = "RPG|Inventory")
    bool TryAddItem(URPGItemObject* Item);

    UFUNCTION(BlueprintCallable, Category = "RPG|Inventory")
    bool IsSlotsAvailable(const URPGItemObject* Item, const int32 TopLeftIndex);

    UFUNCTION(BlueprintCallable, Category = "RPG|Inventory")
    void AddItem(URPGItemObject* Item, const int32 TopLeftIndex);

    UFUNCTION(BlueprintPure, Category = "RPG|Inventory")
    int32 SlotToIndex(const FIntPoint Slot) const;

    UPROPERTY(BlueprintAssignable, Category = "RPG|Inventory")
    FOnInventoryUpdatedDelegate OnInventoryUpdatedDelegate;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Inventory")
    int32 Rows;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Inventory")
    int32 Columns;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Inventory")
    float SlotSize;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Inventory")
    TArray<URPGItemObject*> Items;

    bool TryAddItemToStack(URPGItemObject* InItem);

    virtual void BeginPlay() override;

private:
    FIntPoint IndexToSlot(const int32 Index) const;

    bool IsSlotValid(const FIntPoint Slot) const;

    bool IsNotEmptySlotByIndex(const int32 InIndex);
};
