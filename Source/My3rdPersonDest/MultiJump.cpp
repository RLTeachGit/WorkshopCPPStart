// Fill out your copyright notice in the Description page of Project Settings.

#include "MultiJump.h"




bool UMultiJump::ItemStart(APlayerControllerRL* Controller, TSubclassOf<UUserWidget> UIImageClass)
{
	Super::ItemStart(Controller,UIImageClass);
	APlayerCharacter*	tPC=Controller->GetPlayerCharacter();
	if (tPC != nullptr)
	{
		tPC->JumpMaxCount = 2;
	}
	LifeTime = 20.0f;	//Last 20 seconds		
	return	true;
}

void UMultiJump::ItemStop(APlayerControllerRL* Controller)
{
	Super::ItemStop(Controller);
	APlayerCharacter*	tPC = Controller->GetPlayerCharacter();
	if (tPC != nullptr)
	{
		tPC->JumpMaxCount = 1;
	}
}