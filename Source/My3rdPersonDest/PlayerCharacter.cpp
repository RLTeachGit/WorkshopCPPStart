// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::StartJump);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::ForwardMove);
	PlayerInputComponent->BindAxis("LookRight", this, &APlayerCharacter::TurnRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::AddControllerPitchInput);
}

void APlayerCharacter::StartJump()
{
	Jump();
}

void APlayerCharacter::ForwardMove(float Speed)
{
	if (Controller != NULL)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation(); //Get characters current rotation
		const FVector	Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X); //Generate vector in forward direction
		AddMovementInput(Direction, Speed); //Tell Character to move
	}
}

void APlayerCharacter::TurnRight(float Speed)
{
	if (Controller != NULL)
	{
		// find out which way is right
		AddControllerYawInput(Speed);
	}
}

