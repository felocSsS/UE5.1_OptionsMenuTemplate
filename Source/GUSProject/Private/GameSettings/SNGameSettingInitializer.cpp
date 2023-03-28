// Fill out your copyright notice in the Description page of Project Settings.

#include "GameSettings/SNGameSettingInitializer.h"

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

#undef LOCTEXT_NAMESPACE