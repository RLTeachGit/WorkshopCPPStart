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
     UE_LOG(LogTemp, Warning, TEXT("Collision"));
    // Other Actor is the actor that triggered the event. Check that is not ourself.
    if ( (OtherActor != nullptr ) && (OtherActor != this) && ( OtherComp != nullptr ) )
    {
        APickup* tPickup=Cast<APickup>(OtherActor);
        if(tPickup!=nullptr)
        {
            tPickup->PickedUp(this);
        }
    }
}

void APlayerCharacter::AddItem(UInventoryItem* InventoryItem)
{
    InventoryArray.Add(InventoryItem);
}


// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::StartJump);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::ForwardMove);
	PlayerInputComponent->BindAxis("LookRight", this, &APlayerCharacter::TurnRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::CameraUp);
}

void APlayerCharacter::StartJump()
{
	Jump();
}

float   Clamp(const float Number,const float Low, const float High)
{
    if(Number>High) return High;
    else if(Number < Low) return Low;
    return Number;
}

void    APlayerCharacter::CameraUp(float Speed)
{
    CamAngle= Clamp(CamAngle+Speed,-45.0f,45.0f);
    RotateCamera(CamAngle);
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

