// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItem.generated.h"

/**
 * 
 */
UCLASS()
class MY3RDPERSONDEST_API UInventoryItem : public UObject
{
	GENERATED_BODY()

public:
    virtual int GetID();
	
};
