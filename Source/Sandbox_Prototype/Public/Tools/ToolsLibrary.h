// Copyright Nexus Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ToolsLibrary.generated.h"

/**
 *
 */
UCLASS()
class SANDBOX_PROTOTYPE_API UToolsLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Tools")
    static TArray<FName> GetBoneNames(USkeletalMesh* InMesh);
};
