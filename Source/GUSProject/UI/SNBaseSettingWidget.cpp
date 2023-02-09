// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/SNBaseSettingWidget.h"
#include "Settings/SNGameSetting.h"

void USNBaseSettingWidget::Init(USNGameSetting* InSetting)
{
	Setting = MakeWeakObjectPtr(InSetting);
	if (!Setting.IsValid()) return;

	UpdateWidgetInfo();
}

void USNBaseSettingWidget::UpdateWidgetInfo()
{
	
}
