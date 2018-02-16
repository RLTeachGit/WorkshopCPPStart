// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryItem.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"
#include "Pickup.generated.h"

UCLASS()
class MY3RDPERSONDEST_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


    UPROPERTY(EditAnywhere,BluePrintReadWrite,Category=InventoryItem)
    TSubclassOf<UInventoryItem> InventoryItemSelection;
    
    UInventoryItem* InventoryItem;
	
};
