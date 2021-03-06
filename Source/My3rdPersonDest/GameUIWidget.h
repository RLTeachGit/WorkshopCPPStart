// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "GameUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class MY3RDPERSONDEST_API UGameUIWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void	UpdateUIScore(int Score);
	void	UpdateUIHealth(int Health);

	UUserWidget*  AddInventoryItem(TSubclassOf<UUserWidget>& UIImageClass);

protected:
	UGameUIWidget(const FObjectInitializer& ObjectInitializer);


	// Optionally override the Blueprint "Event Construct" event
	virtual void NativeConstruct() override;

	// Optionally override the tick event
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
    
    
   
    UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category=UI)
    UTextBlock* ScoreWidget;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = UI)
	UTextBlock* HealthWidget;

    
    UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category=UI)
    UPanelWidget* InventoryWidget;

	//Helper function to safely find a UI Element by Name and Type, will Log error if not found
	//As its a template function it needs to be defined in header as it is re-built at compile time
	template	<class UIElement>
	UIElement*	GetUIElementByName(const FName& tName)
	{
		UIElement* tUIElement = Cast<UIElement>(WidgetTree->FindWidget(tName));	//Find Widget & cast to what we expect
		if (tUIElement != nullptr)	//Check its valid
		{
			return	tUIElement;	//Success, we found it
		}
		//Error, wrong type or not found
		UE_LOG(LogTemp, Error, TEXT("GetUIElementByName(%s) Widget Missing"), *tName.ToString());
		return	nullptr;
	}

};
