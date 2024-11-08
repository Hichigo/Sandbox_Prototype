// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"
#include "CreatureTypes.generated.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{
    Player,
    Red,
    Green,
    Blue,
    Yellow,

    None = 255 UMETA(Hidden),  // no team
};

USTRUCT(BlueprintType)
struct FTeamCell
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Creature")
    ETeam Team1;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Creature")
    ETeam Team2;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Creature")
    TEnumAsByte<ETeamAttitude::Type> Attitude;

    FTeamCell()
    {
        Team1 = ETeam::None;
        Team2 = ETeam::None;
        Attitude = ETeamAttitude::Neutral;
    }

    FTeamCell(const ETeam& InTeam1, const ETeam& InTeam2, const ETeamAttitude::Type& InAttitude)
    {
        Team1 = InTeam1;
        Team2 = InTeam2;
        Attitude = InAttitude;
    }
};

USTRUCT(BlueprintType)
struct FAnimDirections
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Creature")
    TMap<FGameplayTag, UAnimMontage*> AttackAnimations;

    FAnimDirections() {}
};