// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "MajorBling.generated.h"

/**
 * 
 */
UCLASS()
class MY3RDPERSONDEST_API UMajorBling : public UInventoryItem
{
	GENERATED_BODY()
	

public:
	virtual	bool	ItemStart(APlayerControllerRL* Controller, TSubclassOf<UUserWidget> UIImageClass) override;
	virtual void	ItemStop(APlayerControllerRL* Controller) override;


};
