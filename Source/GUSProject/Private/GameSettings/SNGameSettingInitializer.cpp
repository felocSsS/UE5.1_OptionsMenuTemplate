// Fill out your copyright notice in the Description page of Project Settings.

#include "GameSettings/SNGameSettingInitializer.h"
#include "GameFramework/InputSettings.h"
#include "GameSettings/SNGameUserSettings.h"
#include "GameSettings/SNGameSetting.h"
#include "GameSettings/SNGameSettingCollection.h"
#include "DataAssets/SNSensitivityDataAsset.h"
#include "Kismet/KismetInternationalizationLibrary.h"

#define LOCTEXT_NAMESPACE "GameUserSettings"

const TArray<FOptionBool> BoolOptions = {
	{LOCTEXT("Bool_On_Loc", "On"), true} ,
	{LOCTEXT("Bool_Off_Loc", "Off"), false} 
};

const TArray<FOptionString> LanguageOptions = {
	{LOCTEXT("English_Loc", "English"), "en"} ,
	{LOCTEXT("Russia_Loc", "Russia"), "ru"} 
};

void USNGameSettingInitializer::Init()
{
}

TArray<USNGameSettingCollection*> USNGameSettingInitializer::GetSettingCollections()
{
	return SettingCollections;
}

void USNGameSettingInitializer_Gameplay::Init()
{
	const auto LanguageCollection = NewObject<USNGameSettingCollection>();
	LanguageCollection->SetCollectionName(LOCTEXT("Language_Loc" , "Language"));

	{
		USNGameSetting_String* Setting = NewObject<USNGameSetting_String>();
		Setting->SetSettingName(LOCTEXT("TextLanguage_Loc" , "Text language"));
		Setting->SetSettingDescription(LOCTEXT("TextLanguageD_Loc", "Text Language description"));
		Setting->SetOptions(LanguageOptions);
		Setting->AddGetterFunc([&]() { return GetLanguage(); } );
		Setting->AddSetterFunc([&](FString Level){ SetLanguage(Level); });
		Setting->WidgetType = EWidgetType::Standard;
		LanguageCollection->AddSettingToCollection(Setting);
	}

	SettingCollections.Add(LanguageCollection);
}

FString USNGameSettingInitializer_Gameplay::GetLanguage() const
{
	return UKismetInternationalizationLibrary::GetCurrentCulture();
}

void USNGameSettingInitializer_Gameplay::SetLanguage(const FString LanguageKey)
{
	UKismetInternationalizationLibrary::SetCurrentCulture(LanguageKey, true);
}

void USNGameSettingInitializer_Video::Init()
{
	auto* UserSettings = USNGameUserSettings::Get();
	if (!UserSettings) return;

	UserSettings->LoadSettings();
	const auto VideoSettings = UserSettings->GetVideoSettings();

	SettingCollections = VideoSettings;
}

void USNGameSettingInitializer_MouseAndKeyboard::Init()
{
	const auto SensitivitySettingsCollection = NewObject<USNGameSettingCollection>();
	SensitivitySettingsCollection->SetCollectionName(LOCTEXT("Sensitivity_Loc" , "Sensitivity"));

	{
		USNGameSetting_Float* Setting = NewObject<USNGameSetting_Float>();
		Setting->SetSettingName(LOCTEXT("MouseSensitivityX_Loc" , "MouseSensitivityX"));
		Setting->SetSettingDescription(LOCTEXT("MouseSensitivityXD_Loc", "MouseSensitivityX description"));
		Setting->AddGetterFunc([&]() { return GetMouseSensitivityX(); } );
		Setting->AddSetterFunc([&](float Level){ SetMouseSensitivityX(Level); });
		Setting->WidgetType = EWidgetType::Slider;
		Setting->SetMinMaxSliderValue(FMinMaxSliderValue{0.0f, 10.0f});
		SensitivitySettingsCollection->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Float* Setting = NewObject<USNGameSetting_Float>();
		Setting->SetSettingName(LOCTEXT("MouseSensitivityY_Loc" , "MouseSensitivityY"));
		Setting->SetSettingDescription(LOCTEXT("MouseSensitivityYD_Loc", "MouseSensitivityY description"));
		Setting->AddGetterFunc([&]() { return GetMouseSensitivityY(); } );
		Setting->AddSetterFunc([&](float Level){ SetMouseSensitivityY(Level); });
		Setting->WidgetType = EWidgetType::Slider;
		Setting->SetMinMaxSliderValue(FMinMaxSliderValue{0.0f, 10.0f});
		SensitivitySettingsCollection->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Bool* Setting = NewObject<USNGameSetting_Bool>();
		Setting->SetSettingName(LOCTEXT("MouseInvertX_Loc" , "MouseInvertX"));
		Setting->SetSettingDescription(LOCTEXT("MouseInvertXD_Loc", "MouseInvertX description"));
		Setting->SetOptions(BoolOptions);
		Setting->AddGetterFunc([&]() { return GetMouseInvertX(); } );
		Setting->AddSetterFunc([&](bool Level) { SetMouseInvertX(Level); });
		SensitivitySettingsCollection->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_Bool* Setting = NewObject<USNGameSetting_Bool>();
		Setting->SetSettingName(LOCTEXT("MouseInvertY_Loc" , "MouseInvertY"));
		Setting->SetSettingDescription(LOCTEXT("MouseInvertYD_Loc", "MouseInvertY description"));
		Setting->SetOptions(BoolOptions);
		Setting->AddGetterFunc([&]() { return GetMouseInvertY(); } );
		Setting->AddSetterFunc([&](bool Level) { SetMouseInvertY(Level); });
		SensitivitySettingsCollection->AddSettingToCollection(Setting);
	}
	
	const auto DisplaySettingsCollection = NewObject<USNGameSettingCollection>();
	DisplaySettingsCollection->SetCollectionName(LOCTEXT("KeyMapping_Loc" , "Key Mapping"));
	
	{
		USNGameSetting_KeySelector_Action* Setting = NewObject<USNGameSetting_KeySelector_Action>();
		Setting->SetSettingName(LOCTEXT("Jump_Loc" , "Jump"));
		Setting->SetSettingDescription(LOCTEXT("JumpD_Loc", "Jump description"));
		Setting->AddGetterFunc([&](FName ActionName) { return GetSelectedKeys_Action(ActionName); } );
		Setting->AddSetterFunc([&](FName ActionName, FSelectedKeys Keys) { SetKeys_Action(ActionName, Keys); });
		Setting->SetActionOrAxisName("Jump");
		Setting->WidgetType = EWidgetType::KeySelector;
		DisplaySettingsCollection->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_KeySelector_Axis* Setting = NewObject<USNGameSetting_KeySelector_Axis>();
		Setting->SetSettingName(LOCTEXT("MoveForward_Loc" , "Move forward"));
		Setting->SetSettingDescription(LOCTEXT("MoveForwardD_Loc", "Move forward description"));
		Setting->AddGetterFunc([&](FName AxisName) { return GetSelectedKeys_Axis(AxisName); } );
		Setting->AddSetterFunc([&](FName AxisName, FSelectedKeys Keys, float Scale) { SetKeys_Axis(AxisName, Keys, Scale); });
		Setting->SetActionOrAxisName("MoveForward");
		Setting->SetInputType(EInputType::Axis);
		Setting->SetScaleType(EScaleType::Positive);
		Setting->WidgetType = EWidgetType::KeySelector;
		DisplaySettingsCollection->AddSettingToCollection(Setting);
	}
	{
		USNGameSetting_KeySelector_Axis* Setting = NewObject<USNGameSetting_KeySelector_Axis>();
		Setting->SetSettingName(LOCTEXT("MoveBackward_Loc" , "Move backward"));
		Setting->SetSettingDescription(LOCTEXT("MoveBackwardD_Loc", "Move backward description"));
		Setting->AddGetterFunc([&](FName AxisName) { return GetSelectedKeys_Axis(AxisName); } );
		Setting->AddSetterFunc([&](FName AxisName, FSelectedKeys Keys, float Scale) { SetKeys_Axis(AxisName, Keys, Scale); });
		Setting->SetActionOrAxisName("MoveBackward");
		Setting->SetInputType(EInputType::Axis);
		Setting->SetScaleType(EScaleType::Negative);
		Setting->WidgetType = EWidgetType::KeySelector;
		DisplaySettingsCollection->AddSettingToCollection(Setting);
	}

	SettingCollections.Add(SensitivitySettingsCollection);
	SettingCollections.Add(DisplaySettingsCollection);
}

void USNGameSettingInitializer_MouseAndKeyboard::SetSensitivityDataAsset(USNSensitivityDataAsset* DataAsset)
{
	SensitivityDataAsset = DataAsset;
}

float USNGameSettingInitializer_MouseAndKeyboard::GetMouseSensitivityX() const
{
	if (!SensitivityDataAsset) return 0.0f;

	return SensitivityDataAsset->MouseSensitivityX;
}

void USNGameSettingInitializer_MouseAndKeyboard::SetMouseSensitivityX(float InMouseSensitivityX)
{
	if (!SensitivityDataAsset) return;

	SensitivityDataAsset->MouseSensitivityX = InMouseSensitivityX;
}

float USNGameSettingInitializer_MouseAndKeyboard::GetMouseSensitivityY() const
{
	if (!SensitivityDataAsset) return 0.0f;

	return SensitivityDataAsset->MouseSensitivityY;
}

void USNGameSettingInitializer_MouseAndKeyboard::SetMouseSensitivityY(float InMouseSensitivityY)
{
	if (!SensitivityDataAsset) return;

	SensitivityDataAsset->MouseSensitivityY = InMouseSensitivityY;
}

bool USNGameSettingInitializer_MouseAndKeyboard::GetMouseInvertX() const
{
	if (!SensitivityDataAsset) return false;

	return SensitivityDataAsset->bInvertMouseX;
}

void USNGameSettingInitializer_MouseAndKeyboard::SetMouseInvertX(bool InMouseInvertX)
{
	if (!SensitivityDataAsset) return;

	SensitivityDataAsset->bInvertMouseX = InMouseInvertX;
}

bool USNGameSettingInitializer_MouseAndKeyboard::GetMouseInvertY() const
{
	if (!SensitivityDataAsset) return false;

	return SensitivityDataAsset->bInvertMouseY;
}

void USNGameSettingInitializer_MouseAndKeyboard::SetMouseInvertY(bool InMouseInvertY)
{
	if (!SensitivityDataAsset) return;

	SensitivityDataAsset->bInvertMouseY = InMouseInvertY;
}

// action type function

FSelectedKeys USNGameSettingInitializer_MouseAndKeyboard::GetSelectedKeys_Action(FName ActionName) const
{
	const UInputSettings* InputSettings = UInputSettings::GetInputSettings();

	TArray<FInputActionKeyMapping> Keys;
	InputSettings->GetActionMappingByName(ActionName, Keys);

	FInputChord FirstKey;
	FInputChord SecondKey;

	if (Keys.IsValidIndex(0))
		FirstKey.Key = Keys[1].Key; FirstKey.bAlt = Keys[1].bAlt; FirstKey.bCmd = Keys[1].bCmd; FirstKey.bCtrl = Keys[1].bCtrl; FirstKey.bShift = Keys[1].bShift;

	if (Keys.IsValidIndex(1))
		SecondKey.Key = Keys[0].Key; SecondKey.bAlt = Keys[0].bAlt; SecondKey.bCmd = Keys[0].bCmd; SecondKey.bCtrl = Keys[0].bCtrl; SecondKey.bShift = Keys[0].bShift;
	
	return FSelectedKeys
	{
		FirstKey,
		SecondKey
	};
}

void USNGameSettingInitializer_MouseAndKeyboard::SetKeys_Action(FName InActionName, FSelectedKeys Keys)
{
	UInputSettings* InputSettings = UInputSettings::GetInputSettings();

	TArray<FInputActionKeyMapping> KeysToDelete;
	InputSettings->GetActionMappingByName(InActionName, KeysToDelete);

	for (auto KeyMapping : KeysToDelete)
		InputSettings->RemoveActionMapping(KeyMapping);
	
	FInputActionKeyMapping FirstKey;
	FInputActionKeyMapping SecondKey;
	
	FirstKey.ActionName = InActionName; FirstKey.Key = Keys.FirstSelectedKey.Key; FirstKey.bAlt = Keys.FirstSelectedKey.bAlt; FirstKey.bCmd = Keys.FirstSelectedKey.bCmd; FirstKey.bCtrl = Keys.FirstSelectedKey.bCtrl; FirstKey.bShift = Keys.FirstSelectedKey.bShift;
	SecondKey.ActionName = InActionName; SecondKey.Key = Keys.SecondSelectedKey.Key; SecondKey.bAlt = Keys.FirstSelectedKey.bAlt; SecondKey.bCmd = Keys.FirstSelectedKey.bCmd; SecondKey.bCtrl = Keys.FirstSelectedKey.bCtrl; SecondKey.bShift = Keys.FirstSelectedKey.bShift;
	
	InputSettings->AddActionMapping(FirstKey);
	InputSettings->AddActionMapping(SecondKey);
}

// axis type function

FSelectedKeys USNGameSettingInitializer_MouseAndKeyboard::GetSelectedKeys_Axis(FName ActionName) const
{
	const UInputSettings* InputSettings = UInputSettings::GetInputSettings();
	
	TArray<FInputAxisKeyMapping> Keys;
	InputSettings->GetAxisMappingByName(ActionName, Keys);

	FInputChord FirstKey;
	FInputChord SecondKey;

	if (Keys.IsValidIndex(0))
		FirstKey.Key = Keys[1].Key; 

	if (Keys.IsValidIndex(1))
		SecondKey.Key = Keys[0].Key; 
	
	return FSelectedKeys
	{
		FirstKey,
		SecondKey
	};
}

void USNGameSettingInitializer_MouseAndKeyboard::SetKeys_Axis(FName InActionName, FSelectedKeys Keys, float Scale)
{
	UInputSettings* InputSettings = UInputSettings::GetInputSettings();

	TArray<FInputAxisKeyMapping> KeysToDelete;
	InputSettings->GetAxisMappingByName(InActionName, KeysToDelete);
	
	for (auto KeyMapping : KeysToDelete)
		InputSettings->RemoveAxisMapping(KeyMapping);
	
	FInputAxisKeyMapping FirstKey;
	FInputAxisKeyMapping SecondKey;
	
	FirstKey.AxisName = InActionName; FirstKey.Key = Keys.FirstSelectedKey.Key; FirstKey.Scale = Scale;
	SecondKey.AxisName = InActionName; SecondKey.Key = Keys.SecondSelectedKey.Key; SecondKey.Scale = Scale;
	
	InputSettings->AddAxisMapping(FirstKey);
	InputSettings->AddAxisMapping(SecondKey);
}

#undef LOCTEXT_NAMESPACE