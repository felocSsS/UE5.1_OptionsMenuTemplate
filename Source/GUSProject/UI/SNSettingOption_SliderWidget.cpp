// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/SNSettingOption_SliderWidget.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Settings/SNGameSetting.h"

void USNSettingOption_SliderWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	ProgressSlider->OnValueChanged.AddDynamic(this, &ThisClass::OnSliderValueChanged);
}

void USNSettingOption_SliderWidget::UpdateWidgetInfo()
{
	if (Setting.IsValid())
	{
		SettingDisplayName->SetText(Setting->GetSettingName());
		ProgressSlider->SetValue(Cast<USNGameSetting_Float>(Setting)->GetCurrentValue());
	}
}

void USNSettingOption_SliderWidget::OnSliderValueChanged(float Value)
{
	if(Setting.IsValid())
	{
		Setting->SetValue(Value);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, FString::SanitizeFloat(Value));
	}
}