#include "SandboxEditor.h"
#include "IAssetTools.h"
#include "Actions/FAssetTypeActions_RPGItemData.h"

#define LOCTEXT_NAMESPACE "FSandboxEditorModule"

void FSandboxEditorModule::StartupModule()
{
    IAssetTools& AssetToolsModule = IAssetTools::Get();
    EAssetTypeCategories::Type RPGItemDataAssetType = AssetToolsModule.RegisterAdvancedAssetCategory(  //
        FName(TEXT("RPGItemDataAsset")),                                                               //
        FText::FromString(TEXT("RPG Items"))                                                           //
    );

    TSharedPtr<FAssetTypeActions_RPGItemData> RPGItemDataAssetAction = MakeShareable(new FAssetTypeActions_RPGItemData(RPGItemDataAssetType));
    TSharedPtr<FAssetTypeActions_RPGItemData_Weapon> RPGItemData_WeaponAssetAction =
        MakeShareable(new FAssetTypeActions_RPGItemData_Weapon(RPGItemDataAssetType));

    AssetToolsModule.RegisterAssetTypeActions(RPGItemDataAssetAction.ToSharedRef());
    AssetToolsModule.RegisterAssetTypeActions(RPGItemData_WeaponAssetAction.ToSharedRef());
}

void FSandboxEditorModule::ShutdownModule() {}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSandboxEditorModule, SandboxEditor)