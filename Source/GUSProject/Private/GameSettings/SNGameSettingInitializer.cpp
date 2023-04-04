// Fill out your copyright notice in the Description page of Project Settings.

#include "GameSettings/SNGameSettingInitializer.h"
#include "GameFramework/InputSettings.h"
#include "GameSettings/SNGameUserSettings.h"
#include "GameSettings/SNGameSetting.h"
#include "GameSettings/SNGameSettingCollection.h"

#define LOCTEXT_NAMESPACE "GameUserSettings"

void USNGameSettingInitializer::Init()
{
}

TArray<USNGameSettingCollection*> USNGameSettingInitializer::GetSettingCollections()
{
	return SettingCollections;
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
	const auto DisplaySettingsCollection = NewObject<USNGameSettingCollection>();
	DisplaySettingsCollection->SetCollectionName(FText::FromString("Display"));
	{
		USNGameSetting_KeySelector_Action* Setting = NewObject<USNGameSetting_KeySelector_Action>();
		Setting->SetSettingName(LOCTEXT("AntiAliasingMethod_Loc" , "Jump"));
		Setting->SetSettingDescription(LOCTEXT("AntiAliasingMethodD_Loc", "Lorem ipsum dolor sit amet description"));
		Setting->AddGetterFunc([&](FName ActionName) { return GetSelectedKeys_Action(ActionName); } );
		Setting->AddSetterFunc([&](FName ActionName, FSelectedKeys_Action Keys) { SetKeys_Action(ActionName, Keys); });
		Setting->SetActionOrAxisName("Jump");
		Setting->SetInputType(EInputType::Action);
		Setting->WidgetType = EWidgetType::KeySelector;
		DisplaySettingsCollection->AddSettingToCollection(Setting);
	}

	SettingCollections.Add(DisplaySettingsCollection);
}

FSelectedKeys_Action USNGameSettingInitializer_MouseAndKeyboard::GetSelectedKeys_Action(FName ActionName) const
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
	
	return FSelectedKeys_Action
	{
		FirstKey,
		SecondKey
	};
}

void USNGameSettingInitializer_MouseAndKeyboard::SetKeys_Action(FName InActionName, FSelectedKeys_Action Keys)
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

#undef LOCTEXT_NAMESPACE