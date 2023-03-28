// Fill out your copyright notice in the Description page of Project Settings.

#include "GameSettings/SNGameSettingCollection.h"
#include "GameSettings/SNGameSetting.h"

void USNGameSettingCollection::SetCollectionName(FText InName)
{
	CollectionName = InName;
}

void USNGameSettingCollection::AddSettingToCollection(USNGameSetting* Setting)
{
	if (!Setting) return;

	Settings.Add(Setting);
}

TArray<USNGameSetting*> USNGameSettingCollection::GetSettings() const
{
	return Settings;
}

FText USNGameSettingCollection::GetCollectionName() const
{
	return CollectionName;
}
