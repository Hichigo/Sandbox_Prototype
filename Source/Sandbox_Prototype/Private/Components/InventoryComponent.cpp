// Copyright Nexus Studio. All Rights Reserved.

#include "Components/InventoryComponent.h"
#include "Items/RPGItemObject.h"

DEFINE_LOG_CATEGORY_STATIC(LogUInventoryComponent, All, All);

UInventoryComponent::UInventoryComponent(const FObjectInitializer& ObjectInitializer)  //
    : Super(ObjectInitializer),                                                        //
      Rows(5),                                                                         //
      Columns(5),                                                                      //
      SlotSize(50.0f)                                                                  //
{
    PrimaryComponentTick.bCanEverTick = false;
}

TMap<URPGItemObject*, FIntPoint> UInventoryComponent::GetAllItems() const
{
    TMap<URPGItemObject*, FIntPoint> ResultItems;

    for (int32 i = 0; i < Items.Num(); ++i)
    {
        if (Items[i] && ResultItems.Contains(Items[i]) == false)
        {
            ResultItems.Add(Items[i], IndexToSlot(i));
        }
    }

    return ResultItems;
}

void UInventoryComponent::RemoveItem(const URPGItemObject* Item)
{
    // TODO: maybe add "topleftindex" and remove by dimension?
    bool bRemoved = false;
    for (int32 i = 0; i < Items.Num(); ++i)
    {
        if (Items[i] == Item)
        {
            Items[i] = nullptr;
            bRemoved = true;
        }
    }

    if (bRemoved)
    {
        OnInventoryUpdatedDelegate.Broadcast();
    }
}

bool UInventoryComponent::TryAddItem(URPGItemObject* Item)
{
    if (Item == nullptr)
    {
        return false;
    }

    if (Item->CommonData.UIData.MaxAmountInStack > 1)
    {
        if (TryAddItemToStack(Item))
        {
            // delete Item; // is delete automatically?
            OnInventoryUpdatedDelegate.Broadcast();
            return true;
        }
    }

    for (int32 i = 0; i < Items.Num(); ++i)
    {
        if (IsSlotsAvailable(Item, i))
        {
            AddItem(Item, i);
            return true;
        }
    }

    return false;
}

bool UInventoryComponent::IsSlotsAvailable(const URPGItemObject* Item, const int32 TopLeftIndex)
{
    const FIntPoint Slot = IndexToSlot(TopLeftIndex);
    const int32 X = Slot.X + Item->CommonData.UIData.Dimension.X;
    const int32 Y = Slot.Y + Item->CommonData.UIData.Dimension.Y;
    for (int32 i = Slot.X; i < X; ++i)
    {
        for (int32 j = Slot.Y; j < Y; ++j)
        {
            const FIntPoint CurrentSlot = FIntPoint(i, j);
            if (IsSlotValid(CurrentSlot))
            {
                if (IsNotEmptySlotByIndex(SlotToIndex(CurrentSlot)))
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
    }

    return true;
}

void UInventoryComponent::AddItem(URPGItemObject* Item, const int32 TopLeftIndex)
{
    const FIntPoint Slot = IndexToSlot(TopLeftIndex);
    const int32 X = Slot.X + Item->CommonData.UIData.Dimension.X;
    const int32 Y = Slot.Y + Item->CommonData.UIData.Dimension.Y;
    for (int32 i = Slot.X; i < X; ++i)
    {
        for (int32 j = Slot.Y; j < Y; ++j)
        {
            const int32 Index = SlotToIndex(FIntPoint(i, j));
            Items[Index] = Item;
        }
    }

    OnInventoryUpdatedDelegate.Broadcast();
}

bool UInventoryComponent::TryAddItemToStack(URPGItemObject* InItem)
{
    const FGuid FindID = InItem->CommonData.ID;
    for (URPGItemObject* Item : Items)
    {
        if (Item == nullptr)
        {
            continue;
        }

        if (Item->CommonData.ID == FindID && Item->IsNotFullStack())
        {
            InItem->Amount = Item->AddToStack(InItem->Amount);

            if (InItem->Amount <= 0)
            {
                return true;
            }
        }
    }

    return false;
}

void UInventoryComponent::BeginPlay()
{
    Super::BeginPlay();

    const int32 AmountSlots = Rows * Columns;

    Items.SetNum(AmountSlots, false);
}

FIntPoint UInventoryComponent::IndexToSlot(const int32 Index) const
{
    return FIntPoint(Index % Columns, Index / Columns);
}

int32 UInventoryComponent::SlotToIndex(const FIntPoint Slot) const
{
    return Slot.X + Slot.Y * Columns;
}

bool UInventoryComponent::IsSlotValid(const FIntPoint Slot) const
{
    return Slot.X >= 0 && Slot.Y >= 0 && Slot.X < Columns && Slot.Y < Rows;
}

bool UInventoryComponent::IsNotEmptySlotByIndex(const int32 InIndex)
{
    if (Items.IsValidIndex(InIndex) && Items[InIndex] != nullptr)
    {
        return true;
    }
    return false;
}
