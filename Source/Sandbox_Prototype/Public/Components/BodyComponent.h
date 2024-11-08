// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/AttributeTypes.h"
#include "BodyComponent.generated.h"

class UAttackBodyPartsData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBodyPartHealthChangedDelegate, const FGameplayTag&, BodyPartTag, const TArray<FBodyPart>&, BodyParts);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnconsciousDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLostBodyPartDelegate, const FGameplayTag&, LostBodyPartTag);

UCLASS(Blueprintable, ClassGroup = (RPG), meta = (BlueprintSpawnableComponent))
class SANDBOX_PROTOTYPE_API UBodyComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UBodyComponent(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, Category = "RPG|Damage")
    void MakeDamage(const float Damage, const FName& InHitBone, const FGameplayTag& InDamageTypeTag);

    UPROPERTY(BlueprintAssignable, Category = "RPG|Body part")
    FOnBodyPartHealthChangedDelegate OnBodyPartHealthChangedDelegate;

    UPROPERTY(BlueprintAssignable, Category = "RPG|Body part")
    FOnUnconsciousDelegate OnUnconsciousDelegate;

    UPROPERTY(BlueprintAssignable, Category = "RPG|Body part")
    FOnDeathDelegate OnDeathDelegate;

    UPROPERTY(BlueprintAssignable, Category = "RPG|Body part")
    FOnLostBodyPartDelegate OnLostBodyPartDelegate;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Body part")
    TArray<FBodyPart> BodyParts;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Body part")
    TObjectPtr<UAttackBodyPartsData> AttackBodyPartsData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Body part|Helper")
    FGameplayTag PointDamageTypeTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Body part|Helper")
    FGameplayTag MainBodyPartsTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Body part|Helper")
    FGameplayTag BodyPartAllTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Body part|Helper")
    FGameplayTag BodyPartRandomTag;

    virtual void BeginPlay() override;

private:
    bool IsNotLostBodyPart(const FGameplayTag& BodyPartTag) const;

    void DoDamageToBodyPart(const float Damage, const FGameplayTag& BodyPartTag);

    int32 GetBodyPartIndex(const FGameplayTag& BodyPartTag) const;

    void DoDamageToAllBodyParts(const float Damage);
};
