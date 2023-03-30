// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MainMenu/GameUserSettings/SNBaseSettingOptionWidget.h"
#include "GameSettings/SNGameSetting.h"

void USNBaseSettingOptionWidget::Init(USNGameSetting* InSetting)
{
	Setting = MakeWeakObjectPtr(InSetting);
	if (!Setting.IsValid()) return;

	UpdateWidgetInfo();
}

void USNBaseSettingOptionWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (SetDescriptionBlockTextFunc) SetDescriptionBlockTextFunc(Setting->GetSettingName(), Setting->GetSettingDescription());
}

void USNBaseSettingOptionWidget::UpdateWidgetInfo()
{
	
}
