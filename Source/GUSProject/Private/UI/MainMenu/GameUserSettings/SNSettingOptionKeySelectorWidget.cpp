// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MainMenu/GameUserSettings/SNSettingOptionKeySelectorWidget.h"

#include "SNGameSetting.h"
#include "Components/InputKeySelector.h"
#include "Components/TextBlock.h"

void USNSettingOptionKeySelectorWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	FirstKeySelector->OnKeySelected.AddDynamic(this, &ThisClass::OnKeySelected);
	FirstKeySelector->OnIsSelectingKeyChanged.AddDynamic(this, &ThisClass::OnIsSelectingKeyChanged_1);

	SecondKeySelector->OnKeySelected.AddDynamic(this, &ThisClass::OnKeySelected);
	SecondKeySelector->OnIsSelectingKeyChanged.AddDynamic(this, &ThisClass::OnIsSelectingKeyChanged_2);

	IsStartKeyChanged = true;
}

void USNSettingOptionKeySelectorWidget::OnKeySelected(FInputChord Key)
{
	if (!Setting.IsValid() && IsStartKeyChanged) return;
	
	FInputChord FirstKey;
	FInputChord SecondKey;
	
	FirstKey.Key = FirstKeySelector->SelectedKey.Key; FirstKey.bAlt = FirstKeySelector->SelectedKey.bAlt; FirstKey.bCmd = FirstKeySelector->SelectedKey.bCmd; FirstKey.bCtrl = FirstKeySelector->SelectedKey.bCtrl; FirstKey.bShift = FirstKeySelector->SelectedKey.bShift;
	
	SecondKey.Key = SecondKeySelector->SelectedKey.Key; SecondKey.bAlt = SecondKeySelector->SelectedKey.bAlt; SecondKey.bCmd = SecondKeySelector->SelectedKey.bCmd; SecondKey.bCtrl = SecondKeySelector->SelectedKey.bCtrl; SecondKey.bShift = SecondKeySelector->SelectedKey.bShift;
	
	Setting->SetValue(Cast<USNGameSetting_KeySelector_Base>(Setting)->GetActionOrAxisName(), FSelectedKeys_Action{ FirstKey, SecondKey });
}

void USNSettingOptionKeySelectorWidget::OnIsSelectingKeyChanged_1()
{
	LastSelectedKey = FirstKeySelector->SelectedKey;
}

void USNSettingOptionKeySelectorWidget::OnIsSelectingKeyChanged_2()
{
	LastSelectedKey = SecondKeySelector->SelectedKey;
}

void USNSettingOptionKeySelectorWidget::UpdateWidgetInfo()
{
	if (Setting.IsValid())
	{
		SettingDisplayName->SetText(Setting->GetSettingName());
		FSelectedKeys_Action CurrentKeys = Setting->GetSelectedKeys();

		FirstKeySelector->SelectedKey = CurrentKeys.FirstSelectedKey;
		SecondKeySelector->SelectedKey = CurrentKeys.SecondSelectedKey;
	}	
}