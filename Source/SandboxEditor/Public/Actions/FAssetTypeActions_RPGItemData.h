// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "Data/RPGItemData.h"
#include "Data/RPGItemData_Weapon.h"

class FAssetTypeActions_RPGItemData : public FAssetTypeActions_Base
{
public:
    FAssetTypeActions_RPGItemData(EAssetTypeCategories::Type InCategory);

    virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "FAssetTypeActions_RPGItemData", "Item Data"); };

    virtual FColor GetTypeColor() const override { return FColor(201, 29, 85); }

    virtual UClass* GetSupportedClass() const override { return URPGItemData::StaticClass(); }

    virtual uint32 GetCategories() override { return Category; }

    virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;

    virtual bool HasActions(const TArray<UObject*>& InObjects) const override { return true; }

    virtual void GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) override;

protected:
    EAssetTypeCategories::Type Category;
};

class FAssetTypeActions_RPGItemData_Weapon final : public FAssetTypeActions_RPGItemData
{
public:
    FAssetTypeActions_RPGItemData_Weapon(EAssetTypeCategories::Type InCategory) : FAssetTypeActions_RPGItemData(InCategory) {}

    virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "FAssetTypeActions_RPGItemData_Weapon", "Item Data Weapon"); };

    virtual UClass* GetSupportedClass() const override { return URPGItemData_Weapon::StaticClass(); }
};