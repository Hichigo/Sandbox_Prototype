// Copyright Nexus Studio. All Rights Reserved.

#include "Tools/ToolsLibrary.h"

#include "PhysicsEngine/BodySetup.h"
#include "PhysicsEngine/PhysicsAsset.h"

TArray<FName> UToolsLibrary::GetBoneNames(USkeletalMesh* InMesh)
{
    TArray<FName> BoneNames;

    UPhysicsAsset* PhysicsAsset = InMesh->GetPhysicsAsset();
    for (const TObjectPtr<USkeletalBodySetup>& BS : PhysicsAsset->SkeletalBodySetups)
    {
        BoneNames.Add(BS->BoneName);
    }

    return BoneNames;
}