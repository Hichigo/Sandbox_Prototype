// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Interfaces/AIHelperInterface.h"
#include "Perception/AIPerceptionTypes.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Types/CreatureTypes.h"
#include "AIControllerCore.generated.h"

class ICreatureInterface;
class UAISenseConfig_Sight;
class UStateTreeComponent;

UCLASS(BlueprintType)

class SANDBOX_PROTOTYPE_API AAIControllerCore : public AAIController, public IAIHelperInterface
{
    GENERATED_BODY()

public:
    AAIControllerCore(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, Category = "RPG|AI")
    void ClearCreatureOpponent();

    // Begin IAIHelperInterface
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|AI")
    void SetTargetLocation(const FVector& InLocation);
    void SetTargetLocation_Implementation(const FVector& InLocation);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|AI")
    void AddTargetLocation(const FVector& InLocation);
    void AddTargetLocation_Implementation(const FVector& InLocation);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|AI")
    void SetOpponent(AActor* InActor);
    void SetOpponent_Implementation(AActor* InActor);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|AI")
    void SetInteractActor(AActor* InActor);
    void SetInteractActor_Implementation(AActor* InActor);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|AI")
    void SetAINewActionTag(const FGameplayTag& InActionTag);
    void SetAINewActionTag_Implementation(const FGameplayTag& InActionTag);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|AI")
    void WarnAttack();
    void WarnAttack_Implementation();
    // End IAIHelperInterface

    UFUNCTION(BlueprintCallable, Category = "RPG|AI")
    void RemoveFirstTargetLocation();

protected:
    // 255 - NoTeam
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|AI")
    ETeam Team;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|AI")
    bool bAutoAttack;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|AI")
    float LostSightMinDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|AI")
    TObjectPtr<AActor> CreatureOpponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|AI")
    TObjectPtr<AActor> InteractActor;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RPG|AI")
    TArray<FVector> TargetLocations;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|AI")
    FVector LastOpponentLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|AI")
    FGameplayTag ChangedActionEventTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|AI")
    int32 DefaultSearchLoop;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|AI")
    int32 SearchLoop;

    UPROPERTY()
    TMap<AActor*, float> DamageFromEnemies;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|AI")
    FGameplayTag DefaultActionTag;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|AI|Actions")
    FGameplayTag IdleActionTag;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|AI|Actions")
    FGameplayTag MoveActionTag;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|AI|Actions")
    FGameplayTag RandomMoveActionTag;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|AI|Actions")
    FGameplayTag FightActionTag;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|AI|Actions")
    FGameplayTag InteractActionTag;

    ICreatureInterface* CreatureInterface;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|AI")
    TObjectPtr<UStateTreeComponent> StateTreeAI;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RPG|AI")
    UAIPerceptionComponent* AIPerceptionComp;

    UPROPERTY()
    UAISenseConfig_Sight* SightConfig;

    UFUNCTION()
    void TargetPerceptionUpdatedHandle(AActor* InActor, FAIStimulus Stimulus);

    UFUNCTION()
    void UpdateTargetByAgroHandle();

    virtual void BeginPlay() override;

    UFUNCTION()
    void DamageCauserHandle(AActor* DamageCauser, const float Damage);

    UFUNCTION()
    void DeathHandle();

    UFUNCTION()
    void UnconsciousHandle(bool bIsUnconscious);

    virtual void OnPossess(APawn* InPawn) override;
    virtual void OnUnPossess() override;

    void SendStateTreeAIEvent(const FGameplayTag& InTag, const FName& InOrigin) const;

    bool IsDeadOrUnconscious(const AActor* InActor) const;

    UFUNCTION(BlueprintCallable, Category = "RPG|AI|Actions")
    void SetDefaultActionTag();

    void TrySetMoveActionTag();

private:
    FTimerHandle UpdateAgroTimerHandle;
};
