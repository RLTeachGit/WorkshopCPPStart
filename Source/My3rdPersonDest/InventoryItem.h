// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerCharacter.h"
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

	virtual	bool	ItemStart(APlayerCharacter* Player);
	virtual	void	ItemTick(APlayerCharacter* Player, float DeltaTime);
	virtual void	ItemStop(APlayerCharacter* Player);
	virtual void	ItemExpired(APlayerCharacter* Player);

protected:
	float	LifeTime=-1.0;

};
