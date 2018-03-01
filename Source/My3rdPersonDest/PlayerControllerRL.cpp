// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllerRL.h"


void     APlayerControllerRL::BeginPlay()
{
    Score=0;
    bConnectUIWidgetToPlayer();
    GameUIWidgetRef->UpdateUIScore(Score);
    GetWorld()->GetTimerManager().SetTimer(PlayerTimerHandle, this, &APlayerControllerRL::PlayerTimer, 1.0f, true);
}

void APlayerControllerRL::PlayerTimer()
{
    UE_LOG(LogTemp, Log, TEXT("Tick"));
}

void APlayerControllerRL::SetupInputComponent()
{
	//Bind Controls to functions
	EnableInput(this);		//Pushes Input to this controller
	Super::SetupInputComponent();	//Base class init
	if (InputComponent != nullptr)	//Check we have one
	{
		InputComponent->BindAction("Jump", IE_Pressed, this, &APlayerControllerRL::ControllerJump);
		InputComponent->BindAction("Jump", IE_Released, this, &APlayerControllerRL::ControllerStopJump);
		InputComponent->BindAxis("MoveForward", this, &APlayerControllerRL::ControllerMoveForward);
		InputComponent->BindAxis("LookRight", this, &APlayerControllerRL::ControllerTurnRight);
		InputComponent->BindAxis("LookUp", this, &APlayerControllerRL::ControllerLookUp);
	}
	else //Error, we have no input
	{
		UE_LOG(LogTemp, Error, TEXT("No InputComponent"));
	}
}

void    APlayerControllerRL::Tick(float DeltaTime)
{
   TickItems(DeltaTime);
}

void    APlayerControllerRL::PlayerRespawnTimer()
{
    UE_LOG(LogTemp, Warning, TEXT("Respawn"));
    GetWorld()->GetAuthGameMode()->RestartPlayer(this);
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


void APlayerControllerRL::ControllerStopJump()
{
	auto tPC = GetPlayerCharacter();
	if (tPC != nullptr)
	{
		tPC->StopJumping();
	}
}

//Helper code to find out flavour of CharacterController
APlayerCharacter * APlayerControllerRL::GetPlayerCharacter()
{
	return Cast<APlayerCharacter>(GetPawn());
}

bool    APlayerControllerRL::bIsPlayerDead()
{
    APlayerCharacter* tPC=GetPlayerCharacter();
    return  ((tPC==nullptr) || tPC->IsDeathPending()); //uses || as a short circuit operator, if first condition true, second wont evaluate
}


bool    APlayerControllerRL::bConnectUIWidgetToPlayer()
{
    if (GameUIWidgetClass != nullptr)        //Use UP BP class set as default in Level BP which inherits this
    {
        //Use Class ref of UI BP which is set in Level Default
        GameUIWidgetRef = NewObject<UGameUIWidget>(this, GameUIWidgetClass);        //Create the UP from its Blueprint
        if (GameUIWidgetRef != nullptr)        //Check its valid
        {
            GameUIWidgetRef->AddToViewport(0);        //Show it
            GameUIWidgetRef->SetOwningPlayer(this);        //Make the Player Controller the owner of the UI
            UE_LOG(LogTemp, Warning, TEXT("Got UI linked to player"));    //Debug
            return  true;   //Success
        }
    }
    UE_LOG(LogTemp, Error, TEXT("bConnectUIWidgetToPlayer() failed"));
    return  false;      //Error, something did not initalise
}

void APlayerControllerRL::AddScore(int Value)
{
    Score += Value;
    if(GameUIWidgetRef!=nullptr)
    {
        GameUIWidgetRef->UpdateUIScore(Score);
    }
}
int APlayerControllerRL::GetScore()
{
    return Score;
}


void    APlayerControllerRL::TickItems(float DeltaTime)
{
    if(!bIsPlayerDead())
    {
        ItemTickTimeout += DeltaTime;
        if (ItemTickTimeout > 1.0f)
        {
            int    tItemCount = InventoryArray.Num();
            if (tItemCount > 0)
            {
                for (int tIndex = tItemCount - 1; tIndex >= 0; tIndex--)    //For all Items in inventory, backwards as it may remove items, causing arrayitems to ripple down
                {
                    InventoryArray[tIndex]->ItemTick(this, ItemTickTimeout);        //Tick the item every second
                }
            }
            ItemTickTimeout = 0.0f;
        }
    }
}


//Get Player to add new Pickup To array
void APlayerControllerRL::AddItem(TSubclassOf<UInventoryItem>  InventoryItemClass,TSubclassOf<UUserWidget> UIImageClass)
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

void APlayerControllerRL::RemoveItem(UInventoryItem * InventoryItem)
{
    if (InventoryArray.RemoveSingle(InventoryItem) != 0)
    {
        InventoryItem->ItemStop(this);
    }
}

void APlayerControllerRL::PlayerDied()
{
    GetWorld()->GetTimerManager().SetTimer(PlayerRespawnTimerHandle, this, &APlayerControllerRL::PlayerRespawnTimer, 5.0f, false);
}


