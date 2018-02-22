// Fill out your copyright notice in the Description page of Project Settings.

#include "GameUIWidget.h"


//UIWidget Constuctor
UGameUIWidget::UGameUIWidget(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{
}

void UGameUIWidget::NativeConstruct()
{
	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();
    ScoreWidget = nullptr;		//Initalise Link to Score Widget, this will be found first time its needed
}


UUserWidget*    UGameUIWidget::AddInventoryItem(TSubclassOf<UUserWidget>& UIImageClass)
{
    const FName GridControlName = FName(TEXT("InventoryPlaceholder"));        //This must match name in the BP
    if (InventoryWidget == nullptr)        //If not yet set, then find it first timne and set a reference
    {
        InventoryWidget = GetUIElementByName<UHorizontalBox>(GridControlName);    //Find Grid Widget
    }
    if (InventoryWidget != nullptr)
    {
        UUserWidget* tItem = NewObject<UUserWidget>(this,UIImageClass);        //Make up the correct item for this pickup, based on
        if(tItem!=nullptr)
        {
            InventoryWidget->AddChild(tItem);
            return  tItem;
        }
    }
    return nullptr;
}

void UGameUIWidget::UpdateUIScore(int Score)
{
	const FName TextControlName = FName(TEXT("ScorePlaceholder"));		//This must match name in the BP
	if (ScoreWidget == nullptr)		//If not yet set, then find it first timne and set a reference
	{
		ScoreWidget = GetUIElementByName<UTextBlock>(TextControlName);	//Find Widget
	}

	if (ScoreWidget != nullptr)	//Paranoia check, in case its been removed from BP
	{
		ScoreWidget->SetText(FText::FromString(FString::Printf(TEXT("Score %d"), Score)));
	}
}



void UGameUIWidget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	// Make sure to call the base class's NativeTick function
	Super::NativeTick(MyGeometry, InDeltaTime);
}
