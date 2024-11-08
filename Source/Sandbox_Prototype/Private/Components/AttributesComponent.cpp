// Copyright Nexus Studio. All Rights Reserved.

#include "Components/AttributesComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogUAttributesComponent, All, All);

UAttributesComponent::UAttributesComponent(const FObjectInitializer& ObjectInitializer)  //
    : Super(ObjectInitializer),                                                          //
      AmountAttributes(0),                                                               //
      LimitAttributes(300)                                                               //
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UAttributesComponent::ApplyAttributeExp(const FGameplayTag& InTypeTag, const float InExp)
{
    const int32 AttributeIndex = GetAttributeIndexByTag(InTypeTag);
    if (AttributeIndex >= 0)
    {
        FAttribute& Attr = Attributes[AttributeIndex];

        if (Attr.ModeTag.MatchesTagExact(IncreaseModeTag) && CanIncreaseAttribute())
        {
            Attr.Exp.Current += InExp;

            while (Attr.Exp.Current >= Attr.Exp.Max)
            {
                Attr.Value += 1;

                AmountAttributes++;

                Attr.Exp.Current -= Attr.Exp.Max;

                UpdateAttributeMaxExp(Attr);
            }
        }
        else if (Attr.ModeTag.MatchesTagExact(DecreaseModeTag) && Attr.Value > 1)
        {
            Attr.Exp.Current -= InExp;

            while (Attr.Exp.Current <= 0 && Attr.Value > 1)
            {
                Attr.Value -= 1;

                AmountAttributes--;

                UpdateAttributeMaxExp(Attr);

                Attr.Exp.Current += Attr.Exp.Max;
            }
        }

        OnChangedAttributeDelegate.Broadcast(Attr);
    }
}

void UAttributesComponent::ChangedAttributeMode(const FGameplayTag& TypeTag, const FGameplayTag& ModeTag)
{
    const int32 AttributeIndex = GetAttributeIndexByTag(TypeTag);
    if (AttributeIndex >= 0)
    {
        FAttribute& Attr = Attributes[AttributeIndex];
        Attr.ModeTag = ModeTag;
    }
}

int32 UAttributesComponent::GetAttributeIndexByTag(const FGameplayTag& InTag)
{
    int32 ResultIndex = -1;
    for (int32 i = 0; i < Attributes.Num(); ++i)
    {
        if (Attributes[i].TypeTag.MatchesTagExact(InTag))
        {
            ResultIndex = i;
            break;
        }
    }

    return ResultIndex;
}

bool UAttributesComponent::CanIncreaseAttribute() const
{
    return AmountAttributes < LimitAttributes;
}

void UAttributesComponent::UpdateAllAttributeMaxExp()
{
    for (FAttribute& Attr : Attributes)
    {
        UpdateAttributeMaxExp(Attr);
    }
}

void UAttributesComponent::UpdateAttributeMaxExp(FAttribute& InAttribute)
{
    FCurveTableRowHandle Handle;
    Handle.CurveTable = ExpAttributesTable;
    Handle.RowName = InAttribute.TableRowName;

    FString ContextString;

    float NextExpValue = 0;

    bool found = Handle.Eval(InAttribute.Value, &NextExpValue, ContextString);

    if (found)
    {
        InAttribute.Exp.Max = NextExpValue;
    }
    else
    {
        UE_LOG(LogUAttributesComponent, Error, TEXT("NOT FOUND TABLE EXP OR ROW!!!!"));
    }
}

void UAttributesComponent::BeginPlay()
{
    Super::BeginPlay();

    UpdateAmountAttributes();

    UpdateAllAttributeMaxExp();
}

void UAttributesComponent::UpdateAmountAttributes()
{
    for (const FAttribute& Attr : Attributes)
    {
        AmountAttributes += Attr.Value;
    }
}
