// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "SNGameUserSettings.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnSettingsUpdatedDelegate);

class USNGameSetting;

UCLASS()
class GUSPROJECT_API USNGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	USNGameUserSettings();

	static USNGameUserSettings* Get();
	
	const TArray<USNGameSetting*>& GetVideoSettings() const;

	void RunBenchmark();

	FOnSettingsUpdatedDelegate OnVideoSettingsUpdate;
	
protected:

private:
	UPROPERTY()
	TArray<USNGameSetting*> VideoSettings;
	
};
