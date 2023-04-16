// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MainMenu/GameUserSettings/SNBaseSettingOptionWidget.h"
#include "GameSettings/SNGameSetting.h"
#include "Components/TextBlock.h"

void USNBaseSettingOptionWidget::Init(USNGameSetting* InSetting)
{
	Setting = InSetting;
	if (!Setting) return;

	UpdateWidgetInfo();
}

void USNBaseSettingOptionWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (SetDescriptionBlockTextFunc && Setting)
		SetDescriptionBlockTextFunc(Setting->GetSettingName(), Setting->GetSettingDescription());
}

void USNBaseSettingOptionWidget::UpdateWidgetInfo()
{
	
}
