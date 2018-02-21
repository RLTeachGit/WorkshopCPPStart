// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllerRL.h"

void APlayerControllerRL::SetupInputComponent()
{
	//Bind Controls to functions
	EnableInput(this);		//Pushes Input to this controller
	Super::SetupInputComponent();	//Base class init
	if (InputComponent != nullptr)	//Check we have one
	{
		InputComponent->BindAction("Jump", IE_Pressed, this, &APlayerControllerRL::ControllerJump);
		InputComponent->BindAxis("MoveForward", this, &APlayerControllerRL::ControllerMoveForward);
		InputComponent->BindAxis("LookRight", this, &APlayerControllerRL::ControllerTurnRight);
		InputComponent->BindAxis("LookUp", this, &APlayerControllerRL::ControllerLookUp);
	}
	else //Error, we have no input
	{
		UE_LOG(LogTemp, Error, TEXT(__FUNCTION__  " No InputComponent"));
	}
}

//Call characters move functions if controller is controlling it

void APlayerControllerRL::ControllerMoveForward(float vSpeed)
{
	auto tPC = GetPlayerCharacter();
	if (tPC != nullptr)
	{
		tPC->PlayerMoveForward(vSpeed);
	}
}

void APlayerControllerRL::ControllerTurnRight(float vSpeed)
{
	auto tPC = GetPlayerCharacter();
	if (tPC != nullptr)
	{
		tPC->PlayerTurnRight(vSpeed);
	}
}

void APlayerControllerRL::ControllerLookUp(float vSpeed)
{
	auto tPC = GetPlayerCharacter();
	if (tPC != nullptr)
	{
		tPC->PlayerCameraUp(vSpeed);
	}
}

void APlayerControllerRL::ControllerJump()
{
	auto tPC = GetPlayerCharacter();
	if (tPC != nullptr)
	{
		tPC->PlayerJump();
	}
}

//Helper code to find out flavour of CharacterController
APlayerCharacter * APlayerControllerRL::GetPlayerCharacter()
{
	return Cast<APlayerCharacter>(GetPawn());
}


