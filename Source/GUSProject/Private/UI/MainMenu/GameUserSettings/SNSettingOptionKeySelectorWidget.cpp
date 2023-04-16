// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MainMenu/GameUserSettings/SNSettingOptionKeySelectorWidget.h"

#include "SNGameSetting.h"
#include "Components/InputKeySelector.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/KismetStringLibrary.h"

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
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, "Key: " + Key.Key.ToString());
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, UKismetStringLibrary::Conv_BoolToString(SecondKeySelector->SelectedKey == Key || Key == LastSelectedKey));
	(SecondKeySelector->SelectedKey == Key && SecondKeySelector->SelectedKey != FInputChord{}) && Key == LastSelectedKey ? FirstKeySelector->SetSelectedKey(LastSelectedKey) : SaveKeys();
}

void USNSettingOptionKeySelectorWidget::OnKeySelected2(FInputChord Key)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, UKismetStringLibrary::Conv_BoolToString(FirstKeySelector->SelectedKey == Key || Key == LastSelectedKey));
	(FirstKeySelector->SelectedKey == Key && FirstKeySelector->SelectedKey != FInputChord{}) && Key == LastSelectedKey ? SecondKeySelector->SetSelectedKey(LastSelectedKey) : SaveKeys();
}

void USNSettingOptionKeySelectorWidget::SaveKeys()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, "JJOJOJOJOJOJ");
	if (!Setting) return;

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
		FirstKeySelector->SetSelectedKey(FInputChord{});
}

void USNSettingOptionKeySelectorWidget::UpdateWidgetInfo()
{
	if (Setting)
	{
		SettingDisplayName->SetText(Setting->GetSettingName());
		const FSelectedKeys CurrentKeys = Setting->GetSelectedKeys();

		FirstKeySelector->SelectedKey = CurrentKeys.FirstSelectedKey;
		SecondKeySelector->SelectedKey = CurrentKeys.SecondSelectedKey;
	}	
}
