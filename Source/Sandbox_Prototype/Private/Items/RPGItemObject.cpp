// Copyright Nexus Studio. All Rights Reserved.

#include "Items/RPGItemObject.h"

bool URPGItemObject::IsStackable() const
{
    return CommonData.UIData.MaxAmountInStack > 1;
}

int32 URPGItemObject::AddToStack(const int32 InAmount)
{
    Amount += InAmount;
    const int32 Remains = Amount - CommonData.UIData.MaxAmountInStack;

    if (Remains > 0)
    {
        Amount -= Remains;
    }

    return Remains;
}