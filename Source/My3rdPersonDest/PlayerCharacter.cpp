// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	USkeletalMeshComponent* tMesh = GetMesh();
	static ConstructorHelpers::FObjectFinder<UMaterial> tLoadedBlingMaterial(TEXT("Material'/Game/Materials/Gold.Gold'"));

	if (tLoadedBlingMaterial.Succeeded())
	{
		BlingMaterial = UMaterialInstanceDynamic::Create(tLoadedBlingMaterial.Object, tMesh);
		DefaultMaterial = tMesh->GetMaterial(0);		//Save Default Old Material
	}
}





// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
    UCapsuleComponent *tCapsule = GetCapsuleComponent();

    tCapsule->OnComponentBeginOverlap.AddDynamic(this,&APlayerCharacter::OnBeginOverlap);
	tCapsule->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnEndOverlap);     //Register the EndOverlap event
	Health = 100.0f;
	bIsDeathPending = false;
	bIsInLava = false;
    UpdateHealthUI(Health);

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsInLava && !bIsDeathPending)
	{
		// Create a damage event  
		TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
		FDamageEvent DamageEvent(ValidDamageTypeClass);

		const float DamageAmount = 1.0f;
		TakeDamage(DamageAmount, DamageEvent, nullptr, this);
	}
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
		else if(OtherActor->ActorHasTag(TEXT("Lava")))	//Stepped in Lava
		{
			bIsInLava = true;
		}
    }
}

void APlayerCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(TEXT("Lava")))	//Stepped out of Lava
	{
		bIsInLava = false;		//Out of Lava
	}
}

float APlayerCharacter::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	// Call the base class - this will tell us how much damage to apply  
	const float tDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (!bIsDeathPending)
	{
		if (tDamage > 0.f)
		{
			Health -= tDamage;
			UE_LOG(LogTemp, Warning, TEXT("Taking Damage %.1f"), Health);
			// If the damage depletes our health set our lifespan  - which will destroy the actor  
			if (Health <= 0.f)
			{
				UpdateHealthUI(0);
				UE_LOG(LogTemp, Warning, TEXT("Dead"));
				bIsDeathPending = true;		//Set Dead Flag
				SetLifeSpan(3.0f);
                auto tController = Cast<APlayerControllerRL>(Controller);
                tController->PlayerDied();
			}
			else
			{
				UpdateHealthUI(Health);
			}
		}
	}
	return tDamage;
}

void	APlayerCharacter::UpdateHealthUI(int vHealth)
{
	auto tController = Cast<APlayerControllerRL>(Controller);
	if (tController != nullptr && tController->GameUIWidgetRef != nullptr)
	{
		tController->GameUIWidgetRef->UpdateUIHealth(vHealth);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::PlayerJump()
{
    if (Controller != NULL && !DeathPending())
    {
        Jump();
    }
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
	if (Controller != NULL && !DeathPending())
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation(); //Get characters current rotation
		const FVector	Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X); //Generate vector in forward direction
		AddMovementInput(Direction, Speed); //Tell Character to move
	}
}

void APlayerCharacter::PlayerTurnRight(float Speed)
{
	if (Controller != NULL && !DeathPending())
	{
		// find out which way is right
		AddControllerYawInput(Speed);
	}
}

bool    APlayerCharacter::DeathPending()
{
    return bIsDeathPending;
}

