// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CreatureInterface.h"
#include "Interfaces/DamageInterface.h"
#include "Interfaces/GameplayInterface.h"
#include "Interfaces/SaveableInterface.h"
#include "Items/RPGItemObject.h"
#include "Types/CreatureTypes.h"
#include "CreatureCore.generated.h"

class AWeaponCore;
class UEquipmentComponent;
class UInventoryComponent;
class UAttributesComponent;
class UBodyComponent;

UCLASS(BlueprintType)
class SANDBOX_PROTOTYPE_API ACreatureCore : public ACharacter,          //
                                            public ICreatureInterface,  //
                                            public IDamageInterface,    //
                                            public IGameplayInterface,  //
                                            public ISaveableInterface   //
{
    GENERATED_BODY()

public:
    ACreatureCore(const FObjectInitializer& ObjectInitializer);

    // Begin Creature interface
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Creature")
    void SetNewActionTag(const FGameplayTag& InActionTag);
    void SetNewActionTag_Implementation(const FGameplayTag& InActionTag);

    UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "RPG|Creature")
    FGameplayTag GetActionTag();
    FGameplayTag GetActionTag_Implementation();

    UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "RPG|Creature")
    AWeaponCore* GetPrimaryWeapon();
    AWeaponCore* GetPrimaryWeapon_Implementation();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Creature")
    void SetPrimaryWeapon(AWeaponCore* InWeapon);
    void SetPrimaryWeapon_Implementation(AWeaponCore* InWeapon);

    UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "RPG|Creature")
    ETeam GetTeam();
    ETeam GetTeam_Implementation();

    virtual FOnUpdateConsciousDelegate& GetUpdateConsciousDelegate() override;
    // End Creature interface

    // Begin Damage interface
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Damage")
    void ReceiveDamage(const FDamageInfo& InDamageInfo);
    void ReceiveDamage_Implementation(const FDamageInfo& InDamageInfo);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Damage")
    void PrepareReceiveDamage(AActor* InDamageCauser);
    void PrepareReceiveDamage_Implementation(AActor* InDamageCauser);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Damage")
    void BeginAttack();
    void BeginAttack_Implementation();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Damage")
    void EndAttack();
    void EndAttack_Implementation();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Damage")
    FGameplayTag GetAttackDirection();
    FGameplayTag GetAttackDirection_Implementation();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Creature")
    bool IsConscious() const;
    bool IsConscious_Implementation() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Creature")
    bool IsAlive() const;
    bool IsAlive_Implementation() const;

    virtual FOnTakeDamageDelegate& GetTakeDamageDelegate() override;
    // End Damage interface

    // Begin IGameplayInterface
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG|Gameplay")
    void Click(AAIController* InAIController);
    void Click_Implementation(AAIController* InAIController);
    // End IGameplayInterface

    virtual void NotifyActorBeginCursorOver() override;
    virtual void NotifyActorEndCursorOver() override;

    virtual void GetActorEyesViewPoint(FVector& Location, FRotator& Rotation) const override;

    UFUNCTION(BlueprintCallable, Category = "RPG|Creature", meta = (ReturnDisplayName = "AnimationLength"))
    float Attack();

    UFUNCTION(BlueprintPure, Category = "RPG|Creature")
    float GetCurrentMontageDuration() const;

    UFUNCTION(BlueprintCallable, Category = "RPG|Creature")
    void AddAttackDirectionTag(const FGameplayTag& InDirectionTag);

    UFUNCTION(BlueprintCallable, Category = "RPG|Creature")
    void RemoveAttackDirectionTag(const FGameplayTag& InDirectionTag);

    UFUNCTION(BlueprintCallable, Category = "RPG|Creature")
    void ClearParryCauser();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RPG|Creature")
    TObjectPtr<AWeaponCore> PrimaryWeapon;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Creature")
    TSubclassOf<UAnimInstance> DefaultAnimationLayerClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RPG|Creature")
    TSubclassOf<UAnimInstance> CurrentAnimationLayerClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RPG|Creature")
    bool bDeath;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RPG|Creature")
    bool bUnconscious;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Creature")
    float UnconsciousTime;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Creature")
    float DelayBetweenAttack;

    // need for delay between attack
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RPG|Creature")
    float LastTimeAttack;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Parry")
    float ParryChance;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Parry")
    UAnimMontage* ParryMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Dodge")
    float DodgeChance;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Dodge")
    UAnimMontage* DodgeMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Hit")
    float HitReactionChance;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Hit")
    UAnimMontage* HitReactionMontage;

    UPROPERTY()
    TObjectPtr<AActor> ParryCauser;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Creature")
    ETeam Team;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Creature")
    FGameplayTag ActionTag;

    FGameplayTag CurrentAttackDirectionTag;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Attack")
    TMap<TSubclassOf<UAnimInstance>, FAnimDirections> AttackAnimationsByLayers;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Attack")
    TMap<FGameplayTag, FName> DirectionsSectionName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Creature|Helper")
    FGameplayTag FightActionTag;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Debug")
    TMap<FGameplayTag, FName> CanBrokenBodyParts;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Creature")
    TObjectPtr<UInventoryComponent> InventoryComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Creature")
    TObjectPtr<UEquipmentComponent> EquipmentComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Creature")
    TObjectPtr<UAttributesComponent> AttributesComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Creature")
    TObjectPtr<UBodyComponent> BodyComponent;

    FOnTakeDamageDelegate OnTakeDamageDelegate;

    UPROPERTY(BlueprintAssignable, Category = "RPG|Creature")
    FOnUpdateConsciousDelegate OnUpdateConsciousDelegate;

    virtual void BeginPlay() override;

    bool CanPlayMontage() const;

    void UpdateAnimationLayer(const TSubclassOf<UAnimInstance>& InAnimationLayerClass);

    UFUNCTION()
    void UnconsciousHandle();

    UFUNCTION()
    void ConsciousHandle();

    UFUNCTION(BlueprintCallable, Category = "RPG|Creature")
    void UpdateConsciousBroadcast();

    UFUNCTION()
    void LostBodyPartHandle(const FGameplayTag& InLostBodyPartTag);

    UFUNCTION()
    void DeathHandle();

    UFUNCTION()
    void EquipItemHandle(const bool bIsEquiped, URPGItemObject* EquipItemObject);

    UAnimMontage* GetAttackAnim();

private:
    FTimerHandle ConsciousTimerHandle;

    FGameplayTagContainer AttackDirectionsTag;
};
