// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacter.h"
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

private:
	void	ControllerMoveForward(float vSpeed);
	void	ControllerTurnRight(float vSpeed);
	void	ControllerLookUp(float vSpeed);
	void	ControllerJump();

public:
	//Helper Function to Access my version of Character
	UFUNCTION(BlueprintCallable)
	APlayerCharacter*	GetPlayerCharacter();

	
};
