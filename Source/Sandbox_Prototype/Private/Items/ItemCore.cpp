// Copyright Nexus Studio. All Rights Reserved.

#include "Items/ItemCore.h"

AItemCore::AItemCore(const FObjectInitializer& ObjectInitializer)  //
    : Super(ObjectInitializer)                                     //
{
    PrimaryActorTick.bCanEverTick = false;
}

void AItemCore::BeginPlay()
{
    Super::BeginPlay();
}
