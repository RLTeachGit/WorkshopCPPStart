// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


class APlayerControllerRL;
class UInventoryItem;


#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerControllerRL.h"
#include "InventoryItem.generated.h"

/**
 * 
 */
UCLASS()
class MY3RDPERSONDEST_API UInventoryItem : public UObject
{
	GENERATED_BODY()

public:

	virtual	bool	ItemStart(APlayerControllerRL* Controller,TSubclassOf<UUserWidget> UIImageClass);
	virtual	void	ItemTick(APlayerControllerRL* Controller, float DeltaTime);
	virtual void	ItemStop(APlayerControllerRL* Controller);
	virtual void	ItemExpired(APlayerControllerRL* Controller);
    
    //Image Widget to display in UI
    UPROPERTY(EditAnywhere,BluePrintReadWrite,Category=InventoryItem)
    TSubclassOf<UUserWidget> UIImageSelector;
    

    UPROPERTY(VisibleAnywhere,BluePrintReadOnly,Category=InventoryItem)
	float	LifeTime=-1.0;
    
protected:
    UUserWidget*    UIImage;

};
