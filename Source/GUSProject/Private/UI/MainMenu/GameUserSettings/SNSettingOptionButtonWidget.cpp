// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MainMenu/GameUserSettings/SNSettingOptionButtonWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "GameSettings/SNGameSetting.h"

void USNSettingOptionButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	NextSettingButton->OnClicked.AddDynamic(this, &ThisClass::OnNextSetting);
	PrevSettingButton->OnClicked.AddDynamic(this, &ThisClass::OnPrevSetting);
}

void USNSettingOptionButtonWidget::UpdateWidgetInfo()
{
	if (Setting.IsValid())
	{
		SettingDisplayName->SetText(Setting->GetSettingName());
		SettingCurrentValue->SetText(Setting->GetCurrentOptionName());
	}
}

void USNSettingOptionButtonWidget::OnNextSetting()
{
	if (Setting.IsValid())
	{
		Setting->ApplyNextOption();
		SettingCurrentValue->SetText(Setting->GetCurrentOptionName());
	}
}

void USNSettingOptionButtonWidget::OnPrevSetting()
{
	if (Setting.IsValid())
	{
		Setting->ApplyPreviousOption();
		SettingCurrentValue->SetText(Setting->GetCurrentOptionName());
	}
}