// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MainMenu/GameUserSettings/SNGameSettingCollectionWidget.h"

#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

void USNGameSettingCollectionWidget::SetCollectionHeaderText(FText InText)
{
	SettingCollectionHeader->SetText(InText);
}

void USNGameSettingCollectionWidget::AddChildToContainer(UUserWidget* SettingWidget)
{
	if (!SettingWidget) return;

	SettingsContainer->AddChild(SettingWidget);
}

TArray<UWidget*> USNGameSettingCollectionWidget::GetChildren() const
{
	return SettingsContainer->GetAllChildren();
}
