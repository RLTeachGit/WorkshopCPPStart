// Fill out your copyright notice in the Description page of Project Settings.

#include "GameUIWidget.h"

UGameUIWidget::UGameUIWidget(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("UGameUIWidget"));
}

void UGameUIWidget::NativeConstruct()
{
	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();
    ScoreWidget = nullptr;
	UE_LOG(LogTemp, Warning, TEXT("NativeConstruct"));
}

void UGameUIWidget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	// Make sure to call the base class's NativeTick function
	Super::NativeTick(MyGeometry, InDeltaTime);
    const FName TextControlName = FName(TEXT("ScorePlaceholder"));
    if(ScoreWidget==nullptr)
    {
        ScoreWidget=(UTextBlock*)(WidgetTree->FindWidget(TextControlName));
        if(ScoreWidget!=nullptr)
        {
            ScoreWidget->SetText(FText::FromString("Can you see your text?"));
        }
    }
}
