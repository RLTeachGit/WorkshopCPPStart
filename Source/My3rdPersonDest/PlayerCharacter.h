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


	//Called from PlayerController
	void	PlayerJump();
	void	PlayerMoveForward(float Speed);
	void	PlayerTurnRight(float Speed);
    void    PlayerCameraUp(float Speed);
    
    UFUNCTION(BlueprintImplementableEvent, Category = Camera)
    void    RotateCamera(float Angle);
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    float     CamAngle=0.0f;
    
    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UMaterialInterface*	DefaultMaterial;
	UMaterialInstanceDynamic* BlingMaterial;
    
//Damage
protected:
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	float	Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	bool	bIsInLava;
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
    bool    bIsDeathPending;

public:
    UFUNCTION()
    bool    DeathPending();

private:
	void	UpdateHealthUI(int vHealth);
};
