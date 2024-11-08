// Copyright Nexus Studio. All Rights Reserved.

#include "AI/AIControllerCore.h"
#include "Components/BodyComponent.h"
#include "Components/StateTreeComponent.h"
#include "Interfaces/CreatureInterface.h"
#include "Interfaces/DamageInterface.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Other/RPGHelperFunctionLibrary.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

DEFINE_LOG_CATEGORY_STATIC(LogAIControllerCore, All, All);

AAIControllerCore::AAIControllerCore(const FObjectInitializer& ObjectInitializer)                                   //
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent"))),  //
      Team(ETeam::None),                                                                                            //
      bAutoAttack(true),                                                                                            //
      LostSightMinDistance(300.0f),                                                                                 //
      DefaultSearchLoop(3),                                                                                         //
      SearchLoop(0)                                                                                                 //
{
    // Cast<UCrowdFollowingComponent>(GetPathFollowingComponent())->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);
    PrimaryActorTick.bCanEverTick = false;

    StateTreeAI = CreateDefaultSubobject<UStateTreeComponent>(TEXT("StateTreeAI"));
    StateTreeAI->SetStartLogicAutomatically(false);

    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
    SightConfig->SightRadius = 1000.0f;
    SightConfig->LoseSightRadius = (SightConfig->SightRadius + 250.0f);
    SightConfig->PeripheralVisionAngleDegrees = 65.0f;
    SightConfig->SetMaxAge(5.0f);
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

    AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComp"));
    AIPerceptionComp->ConfigureSense(*SightConfig);
    AIPerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
}

void AAIControllerCore::ClearCreatureOpponent()
{
    DamageFromEnemies.Remove(CreatureOpponent);
    CreatureOpponent = nullptr;
}

void AAIControllerCore::SetTargetLocation_Implementation(const FVector& InLocation)
{
    TargetLocations.Empty();
    TargetLocations.Add(InLocation);

    ClearCreatureOpponent();

    SetAINewActionTag(MoveActionTag);
}

void AAIControllerCore::AddTargetLocation_Implementation(const FVector& InLocation)
{
    TargetLocations.Add(InLocation);
    TrySetMoveActionTag();
}

void AAIControllerCore::SetOpponent_Implementation(AActor* InActor)
{
    if (InActor != nullptr)
    {
        CreatureOpponent = InActor;
        SetAINewActionTag(FightActionTag);
    }
}

void AAIControllerCore::SetInteractActor_Implementation(AActor* InActor)
{
    InteractActor = InActor;
    SetAINewActionTag(InteractActionTag);
}

void AAIControllerCore::SetAINewActionTag_Implementation(const FGameplayTag& InActionTag)
{
    CreatureInterface->Execute_SetNewActionTag(GetPawn(), InActionTag);
    SendStateTreeAIEvent(ChangedActionEventTag, "AIControllerCore: Changed action tag");
}

void AAIControllerCore::WarnAttack_Implementation()
{
    if (CreatureOpponent != nullptr)
    {
        IDamageInterface::Execute_PrepareReceiveDamage(CreatureOpponent, GetPawn());
    }
}

void AAIControllerCore::RemoveFirstTargetLocation()
{
    if (!TargetLocations.IsEmpty())
    {
        TargetLocations.RemoveAt(0);
    }
}

void AAIControllerCore::TargetPerceptionUpdatedHandle(AActor* InActor, FAIStimulus Stimulus)
{
    if (bAutoAttack == false)
    {
        // for player or passive behaviour
        return;
    }

    if (IsDeadOrUnconscious(GetPawn()) || IsDeadOrUnconscious(InActor))
    {
        return;
    }

    if (URPGHelperFunctionLibrary::IsEnemyTeam(Team, InActor) == false)
    {
        return;
    }

    // lost sight opponent
    if (!Stimulus.WasSuccessfullySensed() && InActor == CreatureOpponent)
    {
        if (GetPawn()->GetDistanceTo(CreatureOpponent) > LostSightMinDistance)
        {
            LastOpponentLocation = CreatureOpponent->GetActorLocation();
            ClearCreatureOpponent();

            DamageFromEnemies.Empty();

            // TODO: change default tag on search opponent tag
            SetAINewActionTag(DefaultActionTag);
            // TODO: checked another sensed actors and get nearly?
            return;
        }
    }

    if (CreatureOpponent == nullptr)
    {
        // sight opponent
        SearchLoop = DefaultSearchLoop;

        SetOpponent(InActor);
    }
}

void AAIControllerCore::UpdateTargetByAgroHandle()
{
    AActor* NewOpponent = nullptr;
    float MaxDamage = 0.0f;
    float* CurrentDamage = DamageFromEnemies.Find(CreatureOpponent);
    if (CurrentDamage)
    {
        MaxDamage = *CurrentDamage;
    }

    for (TPair<AActor*, float> DamageFromEnemy : DamageFromEnemies)
    {
        if (DamageFromEnemy.Key != CreatureOpponent)
        {
            if (DamageFromEnemy.Value > MaxDamage)
            {
                NewOpponent = DamageFromEnemy.Key;
                MaxDamage = DamageFromEnemy.Value;
            }
        }
    }

    if (NewOpponent != nullptr)
    {
        SetOpponent(NewOpponent);
    }
}

void AAIControllerCore::BeginPlay()
{
    Super::BeginPlay();

    AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::TargetPerceptionUpdatedHandle);
}

void AAIControllerCore::DamageCauserHandle(AActor* DamageCauser, const float Damage)
{
    if (CreatureOpponent == nullptr && bAutoAttack)
    {
        SetOpponent(DamageCauser);
    }

    if (bAutoAttack)
    {
        float* CurrentDamage = DamageFromEnemies.Find(DamageCauser);
        if (CurrentDamage)
        {
            *CurrentDamage += Damage;
        }
        else
        {
            DamageFromEnemies.Add(DamageCauser, Damage);
        }

        UpdateTargetByAgroHandle();
    }
}

void AAIControllerCore::DeathHandle()
{
    StateTreeAI->StopLogic("Death");
}

void AAIControllerCore::UnconsciousHandle(bool bIsUnconscious)
{
    if (IDamageInterface::Execute_IsAlive(GetPawn()))
    {
        if (bIsUnconscious)
        {
            ClearCreatureOpponent();
            DamageFromEnemies.Empty();
            StateTreeAI->StopLogic("Unconscious");
        }
        else
        {
            SetDefaultActionTag();
            StateTreeAI->StartLogic();
        }
    }
}

void AAIControllerCore::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    CreatureInterface = Cast<ICreatureInterface>(InPawn);
    if (CreatureInterface)
    {
        Team = CreatureInterface->Execute_GetTeam(InPawn);
        SetGenericTeamId(StaticCast<uint8>(Team));

        SetDefaultActionTag();
        CreatureInterface->GetUpdateConsciousDelegate().AddDynamic(this, &ThisClass::UnconsciousHandle);
    }
    else
    {
        UE_LOG(LogAIControllerCore, Error, TEXT("Controlled creature not implemented CreatureInterface"));
    }

    auto* DamageInterface = Cast<IDamageInterface>(InPawn);
    if (DamageInterface)
    {
        DamageInterface->GetTakeDamageDelegate().AddDynamic(this, &ThisClass::DamageCauserHandle);
    }

    // TODO: may be create logic without body component
    auto* BodyComponent = InPawn->FindComponentByClass<UBodyComponent>();
    if (BodyComponent)
    {
        BodyComponent->OnDeathDelegate.AddDynamic(this, &ThisClass::DeathHandle);
    }

    if (StateTreeAI)
    {
        StateTreeAI->StartLogic();
    }
    else
    {
        UE_LOG(LogAIControllerCore, Error, TEXT("%s: AIControllerCore could not start state tree"), *GetName());
    }
}

void AAIControllerCore::OnUnPossess()
{
    Super::OnUnPossess();

    StateTreeAI->StopLogic("Unpossessed");
}

void AAIControllerCore::SendStateTreeAIEvent(const FGameplayTag& InTag, const FName& InOrigin) const
{
    FStateTreeEvent Event;
    Event.Origin = InOrigin;
    Event.Tag = InTag;

    StateTreeAI->SendStateTreeEvent(Event);
}

bool AAIControllerCore::IsDeadOrUnconscious(const AActor* InActor) const
{
    const auto* DamageInterface = Cast<IDamageInterface>(InActor);
    if (DamageInterface == nullptr)
    {
        return true;
    }

    if (DamageInterface->Execute_IsConscious(InActor) == false)
    {
        return true;
    }

    if (DamageInterface->Execute_IsAlive(InActor) == false)
    {
        return true;
    }

    return false;
}

void AAIControllerCore::SetDefaultActionTag()
{
    SetAINewActionTag(DefaultActionTag);
}

void AAIControllerCore::TrySetMoveActionTag()
{
    const FGameplayTag ActionTag = CreatureInterface->Execute_GetActionTag(GetPawn());
    if (ActionTag.MatchesTagExact(MoveActionTag) == false)
    {
        ClearCreatureOpponent();

        SetAINewActionTag(MoveActionTag);
    }
}
