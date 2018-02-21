// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class   UInventoryItem;
class   APlayerCharacter;


#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Pickup.h"
#include "InventoryItem.h"
#include "GameUIWidget.h"
#include "Components/CapsuleComponent.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class MY3RDPERSONDEST_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void	StartJump();
	void	ForwardMove(float Speed);
	void	TurnRight(float Speed);
    void    CameraUp(float Speed);
    
    UFUNCTION(BlueprintImplementableEvent, Category = Camera)
    void    RotateCamera(float Angle);
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    float     CamAngle=0.0f;
    
    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
    
//PlayerStats
public:
    UFUNCTION()
    void    AddScore(int Value);
    
    UFUNCTION()
    int    GetScore();

private:
    int     Score = 0;

public:
//UI
    UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = UI)
    UGameUIWidget* PlayerUI;

//Inventory
    UPROPERTY(VisibleAnywhere, Instanced, BlueprintReadOnly, Category = Inventory)
    TArray<UInventoryItem*> InventoryArray;
    
    void    AddItem(TSubclassOf<UInventoryItem>  InventoryItemClass,TSubclassOf<UUserWidget> UIImageClass);
	void    RemoveItem(UInventoryItem* InventoryItem);

	float	ItemTickTimeout = 0.0f;

private:
	void	TickItems(float DeltaTime);

};
