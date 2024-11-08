// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/AttributeTypes.h"
#include "AttributesComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedAttributeDelegate, const FAttribute&, Attribute);

UCLASS(Blueprintable, ClassGroup = (RPG), meta = (BlueprintSpawnableComponent))
class SANDBOX_PROTOTYPE_API UAttributesComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UAttributesComponent(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, Category = "RPG|Attribute")
    void ApplyAttributeExp(const FGameplayTag& InTypeTag, const float InExp);

    UFUNCTION(BlueprintCallable, Category = "RPG|Attribute")
    void ChangedAttributeMode(const FGameplayTag& TypeTag, const FGameplayTag& ModeTag);

    UPROPERTY(BlueprintAssignable, Category = "RPG|Attribute")
    FOnChangedAttributeDelegate OnChangedAttributeDelegate;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Attribute")
    TArray<FAttribute> Attributes;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "RPG|Attribute")
    int32 AmountAttributes;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Attribute")
    int32 LimitAttributes;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Attribute")
    TObjectPtr<UCurveTable> ExpAttributesTable;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Attribute|Helper")
    FGameplayTag IncreaseModeTag;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG|Attribute|Helper")
    FGameplayTag DecreaseModeTag;

    int32 GetAttributeIndexByTag(const FGameplayTag& InTag);

    bool CanIncreaseAttribute() const;

    void UpdateAllAttributeMaxExp();

    void UpdateAttributeMaxExp(FAttribute& InAttribute);

    virtual void BeginPlay() override;

    void UpdateAmountAttributes();
};
