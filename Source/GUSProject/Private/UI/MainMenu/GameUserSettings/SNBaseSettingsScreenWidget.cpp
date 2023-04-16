// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MainMenu/GameUserSettings/SNBaseSettingsScreenWidget.h"
#include "SNBaseSettingOptionWidget.h"
#include "SNGameSetting.h"
#include "SNGameSettingCollection.h"
#include "SNGameSettingCollectionWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "SNGameSettingInitializer.h"
#include "SNSettingOptionButtonWidget.h"
#include "SNSettingOptionSliderWidget.h"
#include "Components/Button.h"
#include "SNGameUserSettings.h"
#include "SNSettingOptionKeySelectorWidget.h"
#include "GameFramework/GameUserSettings.h"
#include "DataAssets/SNSensitivityDataAsset.h"

void USNBaseSettingsScreenWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	SettingsCollectionContainer->ClearChildren();
	
	if (!GameSettingInitializer) return;
	GameSettingInitializer->Init();
	
	const auto SettingCollections = GameSettingInitializer->GetSettingCollections();
	
	for (auto const SettingCollection : SettingCollections)
	{
		const auto CollectionWidget = CreateWidget<USNGameSettingCollectionWidget>(this, GameSettingCollectionWidgetClass);
		CollectionWidget->SetCollectionHeaderText(SettingCollection->GetCollectionName());
		
		for (auto const Setting : SettingCollection->GetSettings())
		{
			if (Setting->WidgetType == EWidgetType::Standard)
			{
				const auto SettingsWidget = CreateWidget<USNSettingOptionButtonWidget>(this, GameSettingButtonWidgetClass);
				SettingsWidget->Init(Setting);
				SettingsWidget->SetDescriptionBlockTextFunc = [&](FText HeaderText, FText DescriptionText){ SetDescriptionBlockText(HeaderText, DescriptionText); };
				CollectionWidget->AddChildToContainer(SettingsWidget);
			}
			else if (Setting->WidgetType == EWidgetType::Slider)
			{
				const auto SettingsWidget = CreateWidget<USNSettingOptionSliderWidget>(this, GameSettingSliderWidgetClass);
				SettingsWidget->Init(Setting);
				SettingsWidget->SetDescriptionBlockTextFunc = [&](FText HeaderText, FText DescriptionText){ SetDescriptionBlockText(HeaderText, DescriptionText); };
				CollectionWidget->AddChildToContainer(SettingsWidget);
			}
			else if (Setting->WidgetType == EWidgetType::KeySelector)
			{
				const auto SettingsWidget = CreateWidget<USNSettingOptionKeySelectorWidget>(this, GameSettingKeySelectorWidgetClass);
				SettingsWidget->Init(Setting);
				SettingsWidget->SetDescriptionBlockTextFunc = [&](FText HeaderText, FText DescriptionText){ SetDescriptionBlockText(HeaderText, DescriptionText); };
				CollectionWidget->AddChildToContainer(SettingsWidget);
			}
		}
		SettingsCollectionContainer->AddChild(CollectionWidget);
	}
}

void USNBaseSettingsScreenWidget::SetDescriptionBlockText(FText InDescriptionHeaderText, FText InDescriptionText)
{
	DescriptionHeader->SetText(InDescriptionHeaderText);
	DescriptionText->SetText(InDescriptionText);
}

void USNSettingsScreenWidget_Video::NativeOnInitialized()
{
	GameSettingInitializer = NewObject<USNGameSettingInitializer_Video>();
	
	Super::NativeOnInitialized();

	auto* UserSettings = USNGameUserSettings::Get();
	UserSettings->OnVideoSettingsUpdate.AddUObject(this, &ThisClass::OnVideoSettingsUpdated);

	RunBenchmarkButton->OnClicked.AddDynamic(this, &ThisClass::OnBenchmark);
}

void USNSettingsScreenWidget_Video::OnBenchmark()
{
	auto* UserSettings = USNGameUserSettings::Get();
	if (UserSettings)
	{
		UserSettings->RunBenchmark();
		UserSettings->ApplySettings(false);
	}	
}

void USNSettingsScreenWidget_Video::OnVideoSettingsUpdated()
{
	if (!SettingsCollectionContainer) return;

	for	(auto CollectionWidget : SettingsCollectionContainer->GetAllChildren())
	{
		for (auto Widget : Cast<USNGameSettingCollectionWidget>(CollectionWidget)->GetChildren())
		{
			if (auto* SettingOptionWidget = Cast<USNBaseSettingOptionWidget>(Widget))
			{
				SettingOptionWidget->UpdateWidgetInfo();
			}	
		}
	}
}

void USNSettingsScreenWidget_Audio::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void USNSettingsScreenWidget_Gameplay::NativeOnInitialized()
{
	GameSettingInitializer = NewObject<USNGameSettingInitializer_Gameplay>();
	
	Super::NativeOnInitialized();
}

void USNSettingsScreenWidget_MouseAndKeyboard::NativeOnInitialized()
{
	GameSettingInitializer = NewObject<USNGameSettingInitializer_MouseAndKeyboard>();
	Cast<USNGameSettingInitializer_MouseAndKeyboard>(GameSettingInitializer)->SetSensitivityDataAsset(SensitivityDataAsset);
	
	Super::NativeOnInitialized();
}
