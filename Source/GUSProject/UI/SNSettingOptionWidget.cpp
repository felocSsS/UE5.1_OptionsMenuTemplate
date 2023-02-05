// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/SNSettingOptionWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Settings/SNGameSetting.h"

void USNSettingOptionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	NextSettingButton->OnClicked.AddDynamic(this, &ThisClass::OnNextSetting);
	PrevSettingButton->OnClicked.AddDynamic(this, &ThisClass::OnPrevSetting);
}

void USNSettingOptionWidget::Init(USNGameSetting* InSetting)
{
	Setting = MakeWeakObjectPtr(InSetting);
	if (!Setting.IsValid()) return;
	
	UpdateTexts();
}

void USNSettingOptionWidget::UpdateTexts()
{
	if (Setting.IsValid())
	{
		SettingDisplayName->SetText(Setting->GetSettingName());
		SettingCurrentValue->SetText(Setting->GetCurrentOptionName());
	}
}

void USNSettingOptionWidget::OnNextSetting()
{
	if (Setting.IsValid())
	{
		Setting->ApplyNextOption();
		SettingCurrentValue->SetText(Setting->GetCurrentOptionName());
	}
}

void USNSettingOptionWidget::OnPrevSetting()
{
	if (Setting.IsValid())
	{
		Setting->ApplyPreviousOption();
		SettingCurrentValue->SetText(Setting->GetCurrentOptionName());
	}
}