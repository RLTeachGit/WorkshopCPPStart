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
    UCapsuleComponent *tCapsule = GetCapsuleComponent();

    tCapsule->OnComponentBeginOverlap.AddDynamic(this,&APlayerCharacter::OnBeginOverlap);

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Other Actor is the actor that triggered the event. Check that is not ourself.
    if ( (OtherActor != nullptr ) && (OtherActor != this) && ( OtherComp != nullptr ) )
    {
        APickup* tPickup=Cast<APickup>(OtherActor);		//Check its a Pickup
        if(tPickup!=nullptr)
        {
            auto    tController=Cast<APlayerControllerRL>(GetController());
            tPickup->PickedUp(tController);		//Tell the Pickup its been picked up
        }
    }
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::PlayerJump()
{
	Jump();
}



//Doh! No Clamp in C++ 11
float   Clamp(const float Number,const float Low, const float High)
{
    if(Number>High) return High;
    else if(Number < Low) return Low;
    return Number;
}

void    APlayerCharacter::PlayerCameraUp(float Speed)
{
    CamAngle= Clamp(CamAngle+Speed,-45.0f,45.0f);		//Limit Camera pitch
    RotateCamera(CamAngle);
}

void APlayerCharacter::PlayerMoveForward(float Speed)
{
	if (Controller != NULL)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation(); //Get characters current rotation
		const FVector	Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X); //Generate vector in forward direction
		AddMovementInput(Direction, Speed); //Tell Character to move
	}
}

void APlayerCharacter::PlayerTurnRight(float Speed)
{
	if (Controller != NULL)
	{
		// find out which way is right
		AddControllerYawInput(Speed);
	}
}

