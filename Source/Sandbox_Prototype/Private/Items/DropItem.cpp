// Copyright Nexus Studio. All Rights Reserved.

#include "Items/DropItem.h"

#include "AIController.h"
#include "Components/InventoryComponent.h"
#include "Interfaces/AIHelperInterface.h"
#include "Items/RPGItemObject.h"
#include "Types/RPGTypes.h"

DEFINE_LOG_CATEGORY_STATIC(LogADropItem, All, All);

ADropItem::ADropItem(const FObjectInitializer& ObjectInitializer)  //
    : Super(ObjectInitializer)                                     //
{
    PrimaryActorTick.bCanEverTick = false;

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    StaticMeshComponent->SetLinearDamping(0.5f);
    StaticMeshComponent->SetAngularDamping(1.0f);
    StaticMeshComponent->SetSimulatePhysics(true);
    StaticMeshComponent->SetCollisionObjectType(GMouseInteract);
    StaticMeshComponent->SetCollisionProfileName(GItemProfile, false);
    StaticMeshComponent->SetCustomDepthStencilValue(255);
    RootComponent = StaticMeshComponent;
}

void ADropItem::SetItemObject(URPGItemObject* InItemObject)
{
    ItemObject = InItemObject;
    UpdateComponents();
}

URPGItemObject* ADropItem::GetItemObject() const
{
    return ItemObject;
}

void ADropItem::NotifyActorBeginCursorOver()
{
    StaticMeshComponent->SetRenderCustomDepth(true);
}

void ADropItem::NotifyActorEndCursorOver()
{
    StaticMeshComponent->SetRenderCustomDepth(false);
}

void ADropItem::Click_Implementation(AAIController* InAIController)
{
    const auto* AIHelperInterface = Cast<IAIHelperInterface>(InAIController);
    if (AIHelperInterface)
    {
        AIHelperInterface->Execute_SetInteractActor(InAIController, this);
    }
}

bool ADropItem::Interact_Implementation(AActor* InActor)
{
    if (InActor == nullptr)
    {
        return false;
    }

    auto* Inventory = InActor->FindComponentByClass<UInventoryComponent>();
    if (Inventory == nullptr)
    {
        return false;
    }

    if (Inventory->TryAddItem(ItemObject))
    {
        Destroy();
        return true;
    }

    return false;
}

void ADropItem::BeginPlay()
{
    Super::BeginPlay();
}

void ADropItem::UpdateComponents() const
{
    StaticMeshComponent->SetStaticMesh(ItemObject->CommonData.SpawnItem.StaticMesh);
}
