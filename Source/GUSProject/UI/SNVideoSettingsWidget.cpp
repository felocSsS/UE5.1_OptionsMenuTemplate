// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/SNVideoSettingsWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "SNSettingOptionWidget.h"
#include "GameFramework/GameUserSettings.h"
#include "Settings/SNGameUserSettings.h"

#define LOCTEXT_NAMESPACE "GameUserSettings"

void USNVideoSettingsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	auto* UserSettings = USNGameUserSettings::Get();
	if (!UserSettings) return;

	UserSettings->LoadSettings();
	UserSettings->OnVideoSettingsUpdate.AddUObject(this, &ThisClass::OnVideoSettingsUpdated);
	
	const auto VideoSettings = UserSettings->GetVideoSettings();
	if (!VideoSettingsContainer) return;
	
	VideoSettingsContainer->ClearChildren();

	RunBenchmarkButton->OnClicked.AddDynamic(this, &ThisClass::OnBenchmark);

	GenerateSettings();
	
	for (auto* Setting : VideoSettings)
	{
		const auto SettingWidget = CreateWidget<USNSettingOptionWidget>(this, SettingOptionWidgetClass);
		if (SettingWidget)
		{
			SettingWidget->Init(Setting);
			VideoSettingsContainer->AddChild(SettingWidget);
		}
	}
}

void USNVideoSettingsWidget::OnBenchmark()
{	
	if (auto* UserSettings = GEngine->GetGameUserSettings())
	{
		UserSettings->RunHardwareBenchmark();
		UserSettings->ApplySettings(false);
	}	
}

void USNVideoSettingsWidget::OnVideoSettingsUpdated()
{
	if (!VideoSettingsContainer) return;

	for	(auto* Widget : VideoSettingsContainer->GetAllChildren())
	{
		if (auto* SettingOptionWidget = Cast<USNSettingOptionWidget>(Widget))
		{
			SettingOptionWidget->UpdateTexts();
		}
	}
}

void USNVideoSettingsWidget::GenerateSettings()
{
}

#undef LOCTEXT_NAMESPACE
