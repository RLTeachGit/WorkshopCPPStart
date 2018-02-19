// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();

}

void    APickup::PickedUp(APlayerCharacter* Player)
{
    if(InventoryItemSelection!=nullptr)
    {
        UInventoryItem* tItem = NewObject<UInventoryItem>(Player,InventoryItemSelection);		//Make up the correct item for this pickup, based on what is specified
        if(tItem!=nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("ID %d"), tItem->GetID());	
            Player->AddItem(tItem);	//Tell Player to add item to their inventory
			this->ConditionalBeginDestroy();
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Could not create item"));
        }
    }
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

