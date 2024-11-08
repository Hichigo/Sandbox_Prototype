// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeTypes.h"
#include "GameplayTagContainer.h"
#include "Items/DropItem.h"
#include "ItemTypes.generated.h"

class AWeaponCore;
class ADropItem;

USTRUCT(BlueprintType)
struct FItemUIData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FGameplayTag ItemTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FGameplayTag EquipSlotTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FIntPoint Dimension;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    int32 MaxAmountInStack;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    FBar Durability;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    float Weight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    UMaterialInterface* Icon;

    FItemUIData()
    {
        Name = FText::FromString("{ItemName}");
        Description = FText::FromString("{ItemDescription}");
        Dimension = FIntPoint(1, 1);
        MaxAmountInStack = 1;
        Durability = FBar(1, 1);
        Weight = 0.0f;
        Icon = nullptr;
    }
};

USTRUCT(BlueprintType)
struct FSpawnItem
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    TSubclassOf<ADropItem> SpawnClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    UStaticMesh* StaticMesh;

    FSpawnItem()
    {
        SpawnClass = ADropItem::StaticClass();
        StaticMesh = nullptr;
    }
};

USTRUCT(BlueprintType)
struct FRPGItemInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    FPrimaryAssetType Type;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
    FGuid ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FItemUIData UIData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FSpawnItem SpawnItem;

    FRPGItemInfo() {}
};

USTRUCT(BlueprintType)
struct FWeaponInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float RangeAttack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<AWeaponCore> WeaponClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<UAnimInstance> AnimLayerClass;

    FWeaponInfo()
    {
        Damage = 5.0f;
        RangeAttack = 120.0f;
        WeaponClass = nullptr;
        AnimLayerClass = nullptr;
    }
};

USTRUCT(BlueprintType)
struct FEquipData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    FGameplayTag SlotTag;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
    URPGItemObject* ItemObject;

    FEquipData() { ItemObject = nullptr; }
};