// Copyright Nexus Studio. All Rights Reserved.

#include "Actions/FAssetTypeActions_RPGItemData.h"

FAssetTypeActions_RPGItemData::FAssetTypeActions_RPGItemData(EAssetTypeCategories::Type InCategory)
{
    Category = InCategory;
}

void FAssetTypeActions_RPGItemData::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
    FAssetTypeActions_Base::OpenAssetEditor(InObjects, EditWithinLevelEditor);
}

void FAssetTypeActions_RPGItemData::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder)
{
    FAssetTypeActions_Base::GetActions(InObjects, MenuBuilder);
}