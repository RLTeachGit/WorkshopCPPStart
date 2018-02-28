// Fill out your copyright notice in the Description page of Project Settings.

#include "MajorBling.h"




bool UMajorBling::ItemStart(APlayerControllerRL* Controller, TSubclassOf<UUserWidget> UIImageClass)
{
	Super::ItemStart(Controller, UIImageClass);
	APlayerCharacter*	tPC = Controller->GetPlayerCharacter();
	if (tPC != nullptr)
	{
		USkeletalMeshComponent* tMesh = tPC->GetMesh();
		tMesh->SetMaterial(0, tPC->BlingMaterial);
	}
	LifeTime = 10.0f;	//Last 10 seconds		
	return	true;
}

void UMajorBling::ItemStop(APlayerControllerRL* Controller)
{
	Super::ItemStop(Controller);
	APlayerCharacter*	tPC = Controller->GetPlayerCharacter();
	if (tPC != nullptr && tPC->DefaultMaterial!=nullptr)
	{
		USkeletalMeshComponent* tMesh = tPC->GetMesh();
		tMesh->SetMaterial(0, tPC->DefaultMaterial);
	}
}