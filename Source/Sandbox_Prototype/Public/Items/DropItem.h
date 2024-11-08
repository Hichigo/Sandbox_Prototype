// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/GameplayInterface.h"
#include "Interfaces/SaveableInterface.h"
#include "DropItem.generated.h"

class URPGItemObject;

UCLASS(BlueprintType)
class SANDBOX_PROTOTYPE_API ADropItem : public AActor, public IGameplayInterface, public ISaveableInterface
{
    GENERATED_BODY()

public:
    ADropItem(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, Category = "RPG|Item")
    void SetItemObject(URPGItemObject* InItemObject);

    UFUNCTION(BlueprintPure, Category = "RPG|Item")
    URPGItemObject* GetItemObject() const;

    virtual void NotifyActorBeginCursorOver() override;
    virtual void NotifyActorEndCursorOver() override;

    // Begin IGameplayInterface
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Gameplay")
    void Click(AAIController* InAIController);
    void Click_Implementation(AAIController* InAIController);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Gameplay")
    bool Interact(AActor* InActor);
    bool Interact_Implementation(AActor* InActor);
    // End IGameplayInterface

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Item")
    TObjectPtr<URPGItemObject> ItemObject;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Item")
    TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

    virtual void BeginPlay() override;

private:
    void UpdateComponents() const;
};
