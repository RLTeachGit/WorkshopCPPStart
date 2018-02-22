// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "GameUIWidget.h"
#include "PlayerCharacter.h"
#include "LevelScriptBase.generated.h"

/**
 * 
 */
UCLASS()
class MY3RDPERSONDEST_API ALevelScriptBase : public ALevelScriptActor
{
	GENERATED_BODY()

public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

	//Set this in UI Blueprint Defaults
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	TSubclassOf<UGameUIWidget> GameUIWidgetClass;		//Set Which UI to spawn in derived BP

	//Reference to UI for this level
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
	UGameUIWidget*	GameUIWidgetRef;
    
private:
    bool    bConnectUIWidgetToPlayer();

    

};
