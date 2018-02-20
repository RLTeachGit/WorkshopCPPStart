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
	TickItems(DeltaTime);
}

void	APlayerCharacter::TickItems(float DeltaTime)
{
	ItemTickTimeout += DeltaTime;
	if (ItemTickTimeout > 1.0f)
	{
		int	tItemCount = InventoryArray.Num();
		if (tItemCount > 0)
		{
			for (int tIndex = tItemCount - 1; tIndex >= 0; tIndex--)	//For all Items in inventory, backwards as it may remove items, causing arrayitems to ripple down
			{
				InventoryArray[tIndex]->ItemTick(this, ItemTickTimeout);		//Tick the item every second
			}
		}
		ItemTickTimeout = 0.0f;
	}
}

void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
     UE_LOG(LogTemp, Warning, TEXT("Collision"));
    // Other Actor is the actor that triggered the event. Check that is not ourself.
    if ( (OtherActor != nullptr ) && (OtherActor != this) && ( OtherComp != nullptr ) )
    {
        APickup* tPickup=Cast<APickup>(OtherActor);		//Check its a Pickup
        if(tPickup!=nullptr)
        {
            tPickup->PickedUp(this);		//Tell the Pickup its been picked up
        }
    }
}

//Get Player to add new Pickup To array
void APlayerCharacter::AddItem(TSubclassOf<UInventoryItem>  InventoryItemClass,TSubclassOf<UUserWidget> UIImageClass)
{
    UInventoryItem* tItem = NewObject<UInventoryItem>(this,InventoryItemClass);        //Make up the correct item for this pickup, based on what is specified

    if(tItem!=nullptr)
    {
        if (tItem->ItemStart(this,UIImageClass))    //If items starts OK, add it to Inventory
        {
            InventoryArray.Add(tItem);
        }
    }
}

void APlayerCharacter::RemoveItem(UInventoryItem * InventoryItem)
{
	if (InventoryArray.RemoveSingle(InventoryItem) != 0)
	{
		InventoryItem->ItemStop(this);
	}
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
	if (PlayerUI != nullptr)
	{
		Score += 100;
		PlayerUI->UpdateUIScore(Score);
	}
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

