// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MainMenu/GameUserSettings/SNSettingButtonWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void USNSettingButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SettingButton->OnClicked.AddDynamic(this, &ThisClass::OnSettingButtonClicked);
}

void USNSettingButtonWidget::SetIndex(int32 Index)
{
	IndexOfSettings = Index;
}

void USNSettingButtonWidget::SetButtonText(FText InText)
{
	ButtonText->SetText(InText);
}

void USNSettingButtonWidget::SetOpenWidgetFunc(TFunction<void(int32)> InFunc)
{
	OpenWidgetFunc = InFunc;
}

void USNSettingButtonWidget::OnSettingButtonClicked()
{
	OpenWidgetFunc(IndexOfSettings);
}