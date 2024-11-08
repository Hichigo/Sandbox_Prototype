// Copyright Nexus Studio. All Rights Reserved.

#include "Data/RPGItemData.h"

URPGItemData::URPGItemData()
{
    CommonData.Type = FPrimaryAssetType("Item");
}

FString URPGItemData::GetIdentifierString() const
{
    return GetPrimaryAssetId().ToString();
}

FPrimaryAssetId URPGItemData::GetPrimaryAssetId() const
{
    // This is a DataAsset and not a blueprint so we can just use the raw FName
    // For blueprints you need to handle stripping the _C suffix
    return FPrimaryAssetId(CommonData.Type, GetFName());
}