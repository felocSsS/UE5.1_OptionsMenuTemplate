// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MainMenu/GameUserSettings/SNSettingOptionKeySelectorWidget.h"

#include "SNGameSetting.h"
#include "Components/InputKeySelector.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void USNSettingOptionKeySelectorWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	FirstKeySelector->OnKeySelected.AddDynamic(this, &ThisClass::OnKeySelected1);
	FirstKeySelector->OnIsSelectingKeyChanged.AddDynamic(this, &ThisClass::OnIsSelectingKeyChanged_1);

	SecondKeySelector->OnKeySelected.AddDynamic(this, &ThisClass::OnKeySelected2);
	SecondKeySelector->OnIsSelectingKeyChanged.AddDynamic(this, &ThisClass::OnIsSelectingKeyChanged_2);

	DeleteKeyButton->OnClicked.AddDynamic(this, &ThisClass::USNSettingOptionKeySelectorWidget::OnDeleteKeyButtonClick);
}

void USNSettingOptionKeySelectorWidget::OnKeySelected1(FInputChord Key)
{
	SecondKeySelector->SelectedKey == Key || Key == LastSelectedKey  ? FirstKeySelector->SetSelectedKey(LastSelectedKey) : SaveKeys();
}

void USNSettingOptionKeySelectorWidget::OnKeySelected2(FInputChord Key)
{
	FirstKeySelector->SelectedKey == Key || Key == LastSelectedKey ? SecondKeySelector->SetSelectedKey(LastSelectedKey) : SaveKeys();
}

void USNSettingOptionKeySelectorWidget::SaveKeys()
{
	if (!Setting.IsValid()) return;

	const auto CastedSetting = Cast<USNGameSetting_KeySelector_Base>(Setting);

	FInputChord FirstKey;
	FInputChord SecondKey;

	FirstKey.Key = FirstKeySelector->SelectedKey.Key; FirstKey.bAlt = FirstKeySelector->SelectedKey.bAlt; FirstKey.bCmd = FirstKeySelector->SelectedKey.bCmd; FirstKey.bCtrl = FirstKeySelector->SelectedKey.bCtrl; FirstKey.bShift = FirstKeySelector->SelectedKey.bShift;

	SecondKey.Key = SecondKeySelector->SelectedKey.Key; SecondKey.bAlt = SecondKeySelector->SelectedKey.bAlt; SecondKey.bCmd = SecondKeySelector->SelectedKey.bCmd; SecondKey.bCtrl = SecondKeySelector->SelectedKey.bCtrl; SecondKey.bShift = SecondKeySelector->SelectedKey.bShift;

	switch (CastedSetting->GetInputType())
	{
	case Action:
		Setting->SetValue(CastedSetting->GetActionOrAxisName(), FSelectedKeys{ FirstKey, SecondKey });
		break;

	case Axis:
		Setting->SetValue(CastedSetting->GetActionOrAxisName(), FSelectedKeys{ FirstKey, SecondKey }, Cast<USNGameSetting_KeySelector_Axis>(Setting)->GetScaleType());	
	}
}

void USNSettingOptionKeySelectorWidget::OnIsSelectingKeyChanged_1()
{
	LastSelectedKey = FirstKeySelector->SelectedKey;
}

void USNSettingOptionKeySelectorWidget::OnIsSelectingKeyChanged_2()
{
	LastSelectedKey = SecondKeySelector->SelectedKey;
}

void USNSettingOptionKeySelectorWidget::OnDeleteKeyButtonClick()
{
	if (SecondKeySelector->SelectedKey != FInputChord{})
	{
		SecondKeySelector->SetSelectedKey(FInputChord{});
		return;
	}
	if (FirstKeySelector->SelectedKey != FInputChord{})
	{
		FirstKeySelector->SetSelectedKey(FInputChord{});
	}
}

void USNSettingOptionKeySelectorWidget::UpdateWidgetInfo()
{
	if (Setting.IsValid())
	{
		SettingDisplayName->SetText(Setting->GetSettingName());
		FSelectedKeys CurrentKeys = Setting->GetSelectedKeys();

		FirstKeySelector->SelectedKey = CurrentKeys.FirstSelectedKey;
		SecondKeySelector->SelectedKey = CurrentKeys.SecondSelectedKey;
	}	
}
