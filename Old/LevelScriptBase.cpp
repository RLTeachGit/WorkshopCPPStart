// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelScriptBase.h"

//If this is used as the baseclass for the Level it will set up UI based on UI specified in its Defaults
void ALevelScriptBase::BeginPlay()
{
	Super::BeginPlay();
    bConnectUIWidgetToPlayer();
}

bool    ALevelScriptBase::bConnectUIWidgetToPlayer()
{
    if (GameUIWidgetClass != nullptr)        //Use UP BP class set as default in Level wBP whoch inherits this
    {
        //Use Class ref of UI BP which is set in Level Default
        GameUIWidgetRef = NewObject<UGameUIWidget>(this, GameUIWidgetClass);        //Create the UP from its Blueprint
        if (GameUIWidgetRef != nullptr)        //Check its valid
        {
            APlayerController* tPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
            if (tPlayerController != nullptr)
            {
                APlayerCharacter* tPlayerCharacter = Cast<APlayerCharacter>(tPlayerController->GetPawn());
                if (tPlayerCharacter != nullptr)
                {
                    GameUIWidgetRef->AddToViewport(0);        //Show it
                    tPlayerCharacter->PlayerUI = GameUIWidgetRef;        //Link this UI to the player
                    GameUIWidgetRef->SetOwningPlayer(tPlayerController);        //Make the Player the owner of the UI
                    UE_LOG(LogTemp, Warning, TEXT("Got UI linked to player"));    //Debug
                    return  true;
                }
            }
        }
    }
    return  false;      //Error, something did not initalise
}
