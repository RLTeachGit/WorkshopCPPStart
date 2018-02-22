// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem.h"

bool UInventoryItem::ItemStart(APlayerControllerRL* Controller,TSubclassOf<UUserWidget> UIImageClass)
{
    UIImageSelector=UIImageClass;   //What it will look like in UI
	LifeTime = FMath::RandRange(3.0f,10.0f);
    UIImage=Controller->GameUIWidgetRef->AddInventoryItem(UIImageClass);       //Add Image to UI
    Controller->AddScore(150);
	UE_LOG(LogTemp, Warning, TEXT("Item Started"));
	return	true;
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

void UInventoryItem::ItemStop(APlayerControllerRL* Controller)
{
	UE_LOG(LogTemp, Warning, TEXT("Item Stopped, will destroy"));
    UIImage->RemoveFromParent();
    UIImage=nullptr;
	this->ConditionalBeginDestroy();
}

void UInventoryItem::ItemExpired(APlayerControllerRL* Controller)
{
	UE_LOG(LogTemp, Warning, TEXT("Item Expired, will remove"));
	Controller->RemoveItem(this);	//Remove from player Inventory
}
