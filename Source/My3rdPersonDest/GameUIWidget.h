// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "GameUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class MY3RDPERSONDEST_API UGameUIWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	UGameUIWidget(const FObjectInitializer& ObjectInitializer);

	// Optionally override the Blueprint "Event Construct" event
	virtual void NativeConstruct() override;

	// Optionally override the tick event
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
   
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category=Test)
	int	Test;
	
};
