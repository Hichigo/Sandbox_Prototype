// Copyright Nexus Studio. All Rights Reserved.

#include "Components/EquipmentComponent.h"
#include "Items/RPGItemObject.h"

DEFINE_LOG_CATEGORY_STATIC(LogUEquipmentComponent, All, All);

UEquipmentComponent::UEquipmentComponent(const FObjectInitializer& ObjectInitializer)  //
    : Super(ObjectInitializer)                                                         //
{
    PrimaryComponentTick.bCanEverTick = false;
}

bool UEquipmentComponent::TryEquipItemByIndex(URPGItemObject* ItemObject, const int32 Index)
{
    if (IsEmptySlot(Index))
    {
        EquipItemByIndex(ItemObject, Index);

        return true;
    }
    return false;
}

bool UEquipmentComponent::IsEmptySlot(const int32 Index) const
{
    if (EquipmentData.IsValidIndex(Index) && EquipmentData[Index].ItemObject == nullptr)
    {
        return true;
    }

    return false;
}

bool UEquipmentComponent::IsCorrectTagEquipSlot(const URPGItemObject* ItemObject, const int32 Index) const
{
    if (EquipmentData.IsValidIndex(Index) && EquipmentData[Index].SlotTag.MatchesTagExact(ItemObject->CommonData.UIData.EquipSlotTag))
    {
        return true;
    }

    return false;
}

URPGItemObject* UEquipmentComponent::UnequipItemByIndex(const int32 Index)
{
    URPGItemObject* ResultItemObject = EquipmentData[Index].ItemObject;
    EquipmentData[Index].ItemObject = nullptr;

    OnEquipmentUpdatedDelegate.Broadcast(false, ResultItemObject);

    return ResultItemObject;
}

void UEquipmentComponent::EquipItemByIndex(URPGItemObject* ItemObject, const int32 Index)
{
    EquipmentData[Index].ItemObject = ItemObject;
    // TODO: доработать
    OnEquipmentUpdatedDelegate.Broadcast(true, ItemObject);
}

void UEquipmentComponent::BeginPlay()
{
    Super::BeginPlay();
}
