// Fill out your copyright notice in the Description page of Project Settings.

class APlayerCharacter;		//Forward declaration
class UInventoryItem;


#include "InventoryItem.h"
#include "PlayerCharacter.h"

int UInventoryItem::GetID()
{
    return 10;
}

bool UInventoryItem::ItemStart(APlayerCharacter * Player)
{
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
			Player->RemoveItem(this);
		}
	}
}

void UInventoryItem::ItemStop(APlayerCharacter * Player)
{
	this->ConditionalBeginDestroy();
	UE_LOG(LogTemp, Warning, TEXT("Item Removed"));
}
