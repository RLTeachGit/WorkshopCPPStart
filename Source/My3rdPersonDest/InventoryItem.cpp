// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem.h"

UInventoryItem::UInventoryItem()
{
    UE_LOG(LogTemp, Warning, TEXT("UInventoryItem::UInventoryItem()"));
}

bool UInventoryItem::ItemStart(APlayerControllerRL* Controller,TSubclassOf<UUserWidget> UIImageClass)
{
	UE_LOG(LogTemp, Warning, TEXT("Item Started"));
	UIImageSelector=UIImageClass;   //What it will look like in UI
    UIImage=Controller->GameUIWidgetRef->AddInventoryItem(UIImageClass);       //Add Image to UI
	return	true;
}

void UInventoryItem::ItemStop(APlayerControllerRL* Controller)
{
	UE_LOG(LogTemp, Warning, TEXT("Item Stopped, will destroy"));
	UIImage->RemoveFromParent();
	UIImage = nullptr;
	this->ConditionalBeginDestroy();
}

void UInventoryItem::ItemTick(APlayerControllerRL* Controller,float DeltaTime)
{
    UE_LOG(LogTemp, Warning, TEXT("Item Ticked"));
    if (LifeTime > 0.0)
    {
        LifeTime -= DeltaTime;
        if (LifeTime <= 0.0f)
        {
            ItemExpired(Controller);
        }
    }
}



void UInventoryItem::ItemExpired(APlayerControllerRL* Controller)
{
	UE_LOG(LogTemp, Warning, TEXT("Item Expired, will remove"));
	Controller->RemoveItem(this);	//Remove from player Inventory
}
