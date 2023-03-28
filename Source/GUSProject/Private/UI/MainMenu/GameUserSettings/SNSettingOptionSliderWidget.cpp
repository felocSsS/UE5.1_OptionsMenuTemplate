// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MainMenu/GameUserSettings/SNSettingOptionSliderWidget.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "GameSettings//SNGameSetting.h"

void USNSettingOptionSliderWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	ProgressSlider->OnValueChanged.AddDynamic(this, &ThisClass::OnSliderValueChanged);
}

void USNSettingOptionSliderWidget::UpdateWidgetInfo()
{
	if (Setting.IsValid())
	{
		SettingDisplayName->SetText(Setting->GetSettingName());
		ProgressSlider->SetValue(Cast<USNGameSetting_Float>(Setting)->GetCurrentValue());
	}
}

void USNSettingOptionSliderWidget::OnSliderValueChanged(float Value)
{
	if(Setting.IsValid())
	{
		Setting->SetValue(Value);
	}
}