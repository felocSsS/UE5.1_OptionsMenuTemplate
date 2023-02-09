// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/SNVideoSettingsWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "SNSettingOptionWidget.h"
#include "SNSettingOption_SliderWidget.h"
#include "GameFramework/GameUserSettings.h"
#include "Settings/SNGameUserSettings.h"
#include "Settings/SNGameSetting.h"

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
	
	for (auto* Setting : VideoSettings)
	{
		if (Setting->WidgetType == EWidgetType::Standard)
		{
			const auto SettingWidget = CreateWidget<USNSettingOptionWidget>(this, SettingOptionWidgetClass);
			if (SettingWidget)
			{
				SettingWidget->Init(Setting);
				VideoSettingsContainer->AddChild(SettingWidget);
			}
		}

		if (Setting->WidgetType == EWidgetType::Slider)
		{
			const auto SettingWidget = CreateWidget<USNSettingOption_SliderWidget>(this, SettingOption_SliderWidgetClass);
			if (SettingWidget)
			{
				SettingWidget->Init(Setting);
				VideoSettingsContainer->AddChild(SettingWidget);
			}
		}
			
		/*switch (Setting->WidgetType)
		{
			case Standard:
			{
				const auto SettingWidget = CreateWidget<USNSettingOptionWidget>(this, SettingOptionWidgetClass);
				if (SettingWidget)
				{
					SettingWidget->Init(Setting);
					VideoSettingsContainer->AddChild(SettingWidget);
				}
					break;
			}
			case Slider:
			{
				const auto SettingWidget = CreateWidget<USNSettingOption_SliderWidget>(this, SettingOption_SliderWidgetClass);
				if (SettingWidget)
				{
					SettingWidget->Init(Setting);
					VideoSettingsContainer->AddChild(SettingWidget);
				}
					break;
			}
		}*/
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
		if (auto* SettingOptionWidget = Cast<USNBaseSettingWidget>(Widget))
		{
			SettingOptionWidget->UpdateWidgetInfo();
		}
	}
}

#undef LOCTEXT_NAMESPACE
