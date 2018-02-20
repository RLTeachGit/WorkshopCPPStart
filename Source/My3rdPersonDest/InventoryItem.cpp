// Fill out your copyright notice in the Description page of Project Settings.

class APlayerCharacter;		//Forward declaration
class UInventoryItem;


#include "InventoryItem.h"

int UInventoryItem::GetID()
{
    return 10;
}

bool UInventoryItem::ItemStart(APlayerCharacter * Player,TSubclassOf<UUserWidget> UIImageClass)
{
    UIImageSelector=UIImageClass;   //What it will look like in UI
	LifeTime = 3.0f;
	UE_LOG(LogTemp, Warning, TEXT("Item Started"));
	return	true;
}

void UInventoryItem::ItemTick(APlayerCharacter * Player,float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("Item Ticked"));
	if (LifeTime > 0.0)
	{
		LifeTime -= DeltaTime;
		if (LifeTime <= 0.0f)
		{
			ItemExpired(Player);
		}
	}
}

void UInventoryItem::ItemStop(APlayerCharacter * Player)
{
	UE_LOG(LogTemp, Warning, TEXT("Item Stopped, will destroy"));
	this->ConditionalBeginDestroy();
}

void UInventoryItem::ItemExpired(APlayerCharacter * Player)
{
	UE_LOG(LogTemp, Warning, TEXT("Item Expired, will remove"));
	Player->RemoveItem(this);	//Remove from player Inventory
}
