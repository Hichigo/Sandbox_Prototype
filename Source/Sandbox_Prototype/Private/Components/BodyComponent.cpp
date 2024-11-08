// Copyright Nexus Studio. All Rights Reserved.

#include "Components/BodyComponent.h"
#include "Data/AttackBodyPartsData.h"

UBodyComponent::UBodyComponent(const FObjectInitializer& ObjectInitializer)  //
    : Super(ObjectInitializer)                                               //
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UBodyComponent::MakeDamage(const float Damage, const FName& InHitBone, const FGameplayTag& InDamageTypeTag)
{
    // TODO: get owner resistance and defence and less or multiply damage

    if (InDamageTypeTag.MatchesTagExact(PointDamageTypeTag))
    {
        const FGameplayTag* BodyPartHitTag = AttackBodyPartsData->AttackBodyPart.Find(InHitBone);

        if (BodyPartHitTag && IsNotLostBodyPart(*BodyPartHitTag))
        {
            DoDamageToBodyPart(Damage, *BodyPartHitTag);
            return;
        }
    }

    DoDamageToAllBodyParts(Damage);
}

void UBodyComponent::BeginPlay()
{
    Super::BeginPlay();
}

bool UBodyComponent::IsNotLostBodyPart(const FGameplayTag& BodyPartTag) const
{
    if (BodyPartTag.MatchesTagExact(BodyPartRandomTag))
    {
        return true;
    }

    bool bResult = false;
    for (const FBodyPart& BodyPart : BodyParts)
    {
        if (BodyPart.Tag.MatchesTag(BodyPartTag))
        {
            if (BodyPart.bLost == false)
            {
                bResult = true;
            }
            break;
        }
    }

    return bResult;
}

void UBodyComponent::DoDamageToBodyPart(const float Damage, const FGameplayTag& BodyPartTag)
{
    const int32 BodyPartIndex = GetBodyPartIndex(BodyPartTag);

    auto& CurrentBodyPart = BodyParts[BodyPartIndex];
    FBar& Health = CurrentBodyPart.Health;

    if (Health.Current > 0.0f)
    {
        Health.Current = FMath::Clamp(Health.Current - Damage, 0.0f, Health.Max);
        OnBodyPartHealthChangedDelegate.Broadcast(BodyPartTag, BodyParts);

        if (Health.Current <= 0.0f)
        {
            OnUnconsciousDelegate.Broadcast();
        }
    }
    else if (CurrentBodyPart.bLost == false)
    {
        FBar& HiddenHealth = CurrentBodyPart.HiddenHealth;
        HiddenHealth.Current = FMath::Clamp(HiddenHealth.Current - Damage, 0.0f, HiddenHealth.Max);

        if (HiddenHealth.Current <= 0.0f)
        {
            CurrentBodyPart.bLost = true;
            if (CurrentBodyPart.Tag.MatchesTag(MainBodyPartsTag))
            {
                OnDeathDelegate.Broadcast();
            }
            else
            {
                OnLostBodyPartDelegate.Broadcast(CurrentBodyPart.Tag);
            }
        }
    }
}

int32 UBodyComponent::GetBodyPartIndex(const FGameplayTag& BodyPartTag) const
{
    int32 Result = -1;
    if (BodyPartTag.MatchesTagExact(BodyPartRandomTag))
    {
        // взять массив не потерянных конечностей и выбрать случайный
        Result = FMath::RandHelper(BodyParts.Num());
    }
    else
    {
        for (int32 i = 0; i < BodyParts.Num(); ++i)
        {
            if (BodyParts[i].Tag.MatchesTag(BodyPartTag))
            {
                Result = i;
                break;
            }
        }
    }
    return Result;
}

void UBodyComponent::DoDamageToAllBodyParts(const float Damage)
{
    // TODO: do damage to all body parts: DamageToPart = InDamage / AmountBodyPart
}
