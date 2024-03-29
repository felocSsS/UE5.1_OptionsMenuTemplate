// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SNGameSettingCollection.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "SNGameUserSettings.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnSettingsUpdatedDelegate);

UENUM()
enum class EAntialiasing : uint8
{
	AA_NONE,
	AA_FXAA,
	AA_TAA,
	AA_MSAA,
	AA_TSR
};

UENUM()
enum class EMSAAQuality : uint8
{
	MSAA_NONE,
	MSAA_2X,
	MSAA_4X,	  
	MSAA_8X  
};

class USNGameSettingCollection;
class USoundMix;

UCLASS()
class GUSPROJECT_API USNGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
	
public:
	USNGameUserSettings();

	static USNGameUserSettings* Get();
	
 	const TArray<USNGameSettingCollection*>& GetVideoSettings() const;
 	const TArray<USNGameSettingCollection*>& GetAudioSettings() const;

	void RunBenchmark();

	FOnSettingsUpdatedDelegate OnVideoSettingsUpdate;
	
protected:

private:
	UPROPERTY()
	TArray<TObjectPtr<USNGameSettingCollection>> VideoSettings;

	UPROPERTY()
	TArray<TObjectPtr<USNGameSettingCollection>> AudioSettings;

	// AA_none - 0, AA_FXAA - 1, AA_TAA - 2, AA_MSAA - 3, AA_TSR - 4
	
	int32 GetAAMethod() const;
	void SetAAMethod(int32 InAntialiasingMethod);
	
	int32 GetMSAAQuality() const;
	void SetMSAAQuality(int32 InMSAAQuality);

	float GetMusicVolume() const;
	void SetMusicVolume(float Value);

	float GetSoundEffectsVolume() const;
	void SetSoundEffectsVolume(float Value);

	float GetDialogueVolume() const;
	void SetDialogueVolume(float Value);

	UPROPERTY(config)
	float MusicVolume;
	UPROPERTY(config)
	float SoundEffectsVolume;
	UPROPERTY(config)
	float DialogueVolume;

	UPROPERTY()
	TObjectPtr<USoundMix> SoundMix;
	UPROPERTY()
	TObjectPtr<USoundClass> MusicVolumeClass;
	UPROPERTY()
	TObjectPtr<USoundClass> SoundEffectsVolumeClass;
	UPROPERTY()
	TObjectPtr<USoundClass> DialogueVolumeClass;
	
};