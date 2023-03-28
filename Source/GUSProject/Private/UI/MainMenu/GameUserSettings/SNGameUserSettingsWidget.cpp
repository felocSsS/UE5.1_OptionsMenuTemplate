// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MainMenu/GameUserSettings/SNGameUserSettingsWidget.h"
#include "SNBaseSettingsScreenWidget.h"
#include "SNSettingButtonWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/WidgetSwitcher.h"

void USNGameUserSettingsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	int32 Counter = 0;
	
	SettingsContainer->ClearChildren();
	ButtonsContainer->ClearChildren();
	
	for (auto WidgetClass : SettingsScreenWidgetClasses)
	{
		const auto SettingsScreenWidget = CreateWidget<UUserWidget>(this, WidgetClass.Key);
		SettingsContainer->AddChild(SettingsScreenWidget);
		SettingsContainer->SetActiveWidgetIndex(0);

		const auto ButtonWidget = CreateWidget<USNSettingButtonWidget>(this, SettingsScreenButtonWidgetClass);
		ButtonWidget->SetIndex(Counter);
		ButtonWidget->SetButtonText(WidgetClass.Value); 
		ButtonWidget->SetOpenWidgetFunc([&](int32 Index) { OpenWidget(Index); });
		ButtonsContainer->AddChild(ButtonWidget);
		
		Counter++;
	}
}

void USNGameUserSettingsWidget::OpenWidget(int32 Index)
{
	SettingsContainer->SetActiveWidgetIndex(Index);
}
