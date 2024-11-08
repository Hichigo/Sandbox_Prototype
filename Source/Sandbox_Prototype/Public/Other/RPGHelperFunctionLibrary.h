// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/CreatureTypes.h"
#include "RPGHelperFunctionLibrary.generated.h"

class URPGItemObject;

UCLASS()
class SANDBOX_PROTOTYPE_API URPGHelperFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "RPG|Item", meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
    static void DropItem(UObject* WorldContextObject, URPGItemObject* DropItemObject, const AActor* OwnerItem);

    UFUNCTION(BlueprintCallable, Category = "RPG|Creature")
    static bool IsEnemyTeam(ETeam Team, AActor* Other);

    // rotation via quaternion
    UFUNCTION(BlueprintPure, Category = "RPG|Helper")
    static float YawRotation(const float CurrentYaw, const float TargetYaw, const float DeltaTime, const float InterpSpeed);
};
