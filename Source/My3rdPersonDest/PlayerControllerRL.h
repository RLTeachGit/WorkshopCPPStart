// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacter.h"
#include "GameUIWidget.h"
#include "PlayerControllerRL.generated.h"

/**
 * 
 */
UCLASS()
class MY3RDPERSONDEST_API APlayerControllerRL : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void	SetupInputComponent() override;
    virtual void    BeginPlay() override;
    virtual void    Tick(float DeltaTime) override;

private:
	void	ControllerMoveForward(float vSpeed);
	void	ControllerTurnRight(float vSpeed);
	void	ControllerLookUp(float vSpeed);
	void	ControllerJump();
    bool    bConnectUIWidgetToPlayer();
    
public:
	//Helper Function to Access my version of Character
	UFUNCTION(BlueprintCallable)
	APlayerCharacter*	GetPlayerCharacter();
    
    UFUNCTION(BlueprintCallable)
    bool    bIsPlayerDead();

//UI
    //Set this in UI Blueprint Defaults
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
    TSubclassOf<UGameUIWidget> GameUIWidgetClass;        //Set Which UI to spawn in derived BP

    //Reference to UI for this level
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
    UGameUIWidget*    GameUIWidgetRef;

//PlayerStats
public:
    UFUNCTION()
    void    AddScore(int Value);
    
    UFUNCTION()
    int     GetScore();
    
private:
    int     Score = 0;

public:
    
    //Inventory
    UPROPERTY(VisibleAnywhere, Instanced, BlueprintReadOnly, Category = Inventory)
    TArray<UInventoryItem*> InventoryArray;
    
    void    AddItem(TSubclassOf<UInventoryItem>  InventoryItemClass,TSubclassOf<UUserWidget> UIImageClass);
    void    RemoveItem(UInventoryItem* InventoryItem);

	void	PlayerDied();
    
    float   ItemTickTimeout = 0.0f;
    
private:
    void    TickItems(float DeltaTime);
    
};
