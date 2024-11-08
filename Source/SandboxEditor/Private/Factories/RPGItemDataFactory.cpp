// Copyright Nexus Studio. All Rights Reserved.

#include "Factories/RPGItemDataFactory.h"
#include "Data/RPGItemData.h"

URPGItemDataFactory::URPGItemDataFactory(const FObjectInitializer& ObjectInitializer)  //
    : Super(ObjectInitializer)                                                         //
{
    SupportedClass = URPGItemData::StaticClass();

    bText = false;
    bCreateNew = true;
    bEditorImport = false;
    bEditAfterNew = true;
}

UObject* URPGItemDataFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    URPGItemData* NewItemData = NewObject<URPGItemData>(InParent, InClass, InName, Flags);
    NewItemData->CommonData.ID = FGuid::NewGuid();

    return NewItemData;
}
