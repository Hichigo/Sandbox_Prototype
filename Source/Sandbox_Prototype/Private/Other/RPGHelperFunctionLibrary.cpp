// Copyright Nexus Studio. All Rights Reserved.

#include "Other/RPGHelperFunctionLibrary.h"
#include "Interfaces/CreatureInterface.h"
#include "Items/DropItem.h"
#include "Items/RPGItemObject.h"
#include "Types/CreatureTypes.h"

void URPGHelperFunctionLibrary::DropItem(UObject* WorldContextObject, URPGItemObject* DropItemObject, const AActor* OwnerItem)
{
    if (DropItemObject == nullptr || OwnerItem == nullptr)
    {
        return;
    }

    UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
    if (World == nullptr)
    {
        return;
    }

    const FVector OwnerLocation = OwnerItem->GetActorLocation();
    const FVector ForwardVector = OwnerItem->GetActorForwardVector();
    const float RandomDropRange = FMath::RandRange(150.0f, 250.0f);

    const FVector ForwardLocation = OwnerLocation + ForwardVector * RandomDropRange;
    const FVector StartLocation = ForwardLocation + FVector(0.0f, 0.0f, 200.0f);
    const FVector EndLocation = ForwardLocation - FVector(0.0f, 0.0f, 200.0f);

    FHitResult Hit;
    const bool bSuccess = World->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility);
    FTransform SpawnTransform;

    // clang-format off
    SpawnTransform.SetRotation(FRotator(
        FMath::RandRange(-180.0f, 180.0f),
        FMath::RandRange(-180.0f, 180.0f),
        FMath::RandRange(-180.0f, 180.0f)
        ).Quaternion()
    );
    // clang-format on

    if (bSuccess)
    {
        SpawnTransform.SetLocation(Hit.ImpactPoint + FVector(0.0f, 0.0f, 100.0f));
    }
    else
    {
        SpawnTransform.SetLocation(ForwardLocation);
    }

    auto* DropItem = World->SpawnActorDeferred<ADropItem>(DropItemObject->CommonData.SpawnItem.SpawnClass, SpawnTransform);
    if (DropItem)
    {
        DropItem->SetItemObject(DropItemObject);
        DropItem->FinishSpawning(SpawnTransform);
    }
}

bool URPGHelperFunctionLibrary::IsEnemyTeam(ETeam Team, AActor* Other)
{
    TArray<FTeamCell> TeamsAttitude;

    TeamsAttitude.Add(FTeamCell(ETeam::Player, ETeam::Player, ETeamAttitude::Type::Friendly));
    TeamsAttitude.Add(FTeamCell(ETeam::Player, ETeam::Red, ETeamAttitude::Type::Hostile));
    TeamsAttitude.Add(FTeamCell(ETeam::Player, ETeam::Green, ETeamAttitude::Type::Hostile));
    TeamsAttitude.Add(FTeamCell(ETeam::Player, ETeam::Blue, ETeamAttitude::Type::Friendly));
    TeamsAttitude.Add(FTeamCell(ETeam::Player, ETeam::Yellow, ETeamAttitude::Type::Friendly));

    TeamsAttitude.Add(FTeamCell(ETeam::Red, ETeam::Player, ETeamAttitude::Type::Hostile));
    TeamsAttitude.Add(FTeamCell(ETeam::Red, ETeam::Red, ETeamAttitude::Type::Friendly));
    TeamsAttitude.Add(FTeamCell(ETeam::Red, ETeam::Green, ETeamAttitude::Type::Friendly));
    TeamsAttitude.Add(FTeamCell(ETeam::Red, ETeam::Blue, ETeamAttitude::Type::Hostile));
    TeamsAttitude.Add(FTeamCell(ETeam::Red, ETeam::Yellow, ETeamAttitude::Type::Hostile));

    TeamsAttitude.Add(FTeamCell(ETeam::Green, ETeam::Player, ETeamAttitude::Type::Hostile));
    TeamsAttitude.Add(FTeamCell(ETeam::Green, ETeam::Red, ETeamAttitude::Type::Friendly));
    TeamsAttitude.Add(FTeamCell(ETeam::Green, ETeam::Green, ETeamAttitude::Type::Friendly));
    TeamsAttitude.Add(FTeamCell(ETeam::Green, ETeam::Blue, ETeamAttitude::Type::Hostile));
    TeamsAttitude.Add(FTeamCell(ETeam::Green, ETeam::Yellow, ETeamAttitude::Type::Hostile));

    TeamsAttitude.Add(FTeamCell(ETeam::Blue, ETeam::Player, ETeamAttitude::Type::Friendly));
    TeamsAttitude.Add(FTeamCell(ETeam::Blue, ETeam::Red, ETeamAttitude::Type::Hostile));
    TeamsAttitude.Add(FTeamCell(ETeam::Blue, ETeam::Green, ETeamAttitude::Type::Hostile));
    TeamsAttitude.Add(FTeamCell(ETeam::Blue, ETeam::Blue, ETeamAttitude::Type::Friendly));
    TeamsAttitude.Add(FTeamCell(ETeam::Blue, ETeam::Yellow, ETeamAttitude::Type::Friendly));

    TeamsAttitude.Add(FTeamCell(ETeam::Yellow, ETeam::Player, ETeamAttitude::Type::Friendly));
    TeamsAttitude.Add(FTeamCell(ETeam::Yellow, ETeam::Red, ETeamAttitude::Type::Hostile));
    TeamsAttitude.Add(FTeamCell(ETeam::Yellow, ETeam::Green, ETeamAttitude::Type::Hostile));
    TeamsAttitude.Add(FTeamCell(ETeam::Yellow, ETeam::Blue, ETeamAttitude::Type::Friendly));
    TeamsAttitude.Add(FTeamCell(ETeam::Yellow, ETeam::Yellow, ETeamAttitude::Type::Friendly));

    auto* OtherCreatureInterface = Cast<ICreatureInterface>(Other);
    if (OtherCreatureInterface)
    {
        const ETeam OtherTeam = OtherCreatureInterface->Execute_GetTeam(Other);

        // clang-format off
        const FTeamCell* TeamAttitude = TeamsAttitude.FindByPredicate([&](const FTeamCell& TeamCell)
        {
            return TeamCell.Team1 == Team && TeamCell.Team2 == OtherTeam;
        });
        // clang-format on

        if (TeamAttitude)
        {
            return TeamAttitude->Attitude == ETeamAttitude::Type::Hostile;
        }
    }

    return false;
}

float URPGHelperFunctionLibrary::YawRotation(const float CurrentYaw, const float TargetYaw, const float DeltaTime, const float InterpSpeed)
{
    const FQuat AQuat(FRotator(0.0f, CurrentYaw, 0.0f));
    const FQuat BQuat(FRotator(0.0f, TargetYaw, 0.0f));

    const FQuat Result = FMath::QInterpConstantTo(AQuat, BQuat, DeltaTime, InterpSpeed);

    return Result.Rotator().Yaw;
}