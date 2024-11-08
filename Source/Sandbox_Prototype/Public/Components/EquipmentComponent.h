// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/ItemTypes.h"
#include "EquipmentComponent.generated.h"

class URPGItemObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquipmentUpdatedDelegate, const bool, bIsEquiped, URPGItemObject*, EquipItemObject);

UCLASS(ClassGroup = (RPG), meta = (BlueprintSpawnableComponent))
class SANDBOX_PROTOTYPE_API UEquipmentComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UEquipmentComponent(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, Category = "RPG|Equipment")
    bool TryEquipItemByIndex(URPGItemObject* ItemObject, const int32 Index);

    UFUNCTION(BlueprintPure, Category = "RPG|Equipment")
    bool IsEmptySlot(const int32 Index) const;

    UFUNCTION(BlueprintPure, Category = "RPG|Equipment")
    bool IsCorrectTagEquipSlot(const URPGItemObject* ItemObject, const int32 Index) const;

    // use this function after check "IsEmptySlot"
    UFUNCTION(BlueprintPure, Category = "RPG|Equipment")
    URPGItemObject* UnequipItemByIndex(const int32 Index);

    UPROPERTY(BlueprintAssignable, Category = "RPG|Equipment")
    FOnEquipmentUpdatedDelegate OnEquipmentUpdatedDelegate;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Equipment")
    TArray<FEquipData> EquipmentData;

    void EquipItemByIndex(URPGItemObject* ItemObject, const int32 Index);

    virtual void BeginPlay() override;
};
