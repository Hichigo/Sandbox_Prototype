// Copyright Nexus Studio. All Rights Reserved.

#include "Factories/RPGItemData_WeaponFactory.h"
#include "Data/RPGItemData_Weapon.h"

URPGItemData_WeaponFactory::URPGItemData_WeaponFactory(const FObjectInitializer& ObjectInitializer)  //
    : Super(ObjectInitializer)                                                                       //
{
    SupportedClass = URPGItemData_Weapon::StaticClass();

    bText = false;
    bCreateNew = true;
    bEditorImport = false;
    bEditAfterNew = true;
}

UObject* URPGItemData_WeaponFactory::FactoryCreateNew(
    UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    URPGItemData_Weapon* NewItemData = NewObject<URPGItemData_Weapon>(InParent, InClass, InName, Flags);
    NewItemData->CommonData.ID = FGuid::NewGuid();

    return NewItemData;
}