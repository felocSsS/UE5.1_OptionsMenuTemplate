// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SNSettingOptionWidget.generated.h"

class UTextBlock;
class USNGameSetting;
class UButton;

UCLASS()
class GUSPROJECT_API USNSettingOptionWidget : public UUserWidget
{
	GENERATED_BODY()

public:

protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* SettingDisplayName;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* SettingCurrentValue;

	UPROPERTY(meta=(BindWidget))
	UButton* NextSettingButton;

	UPROPERTY(meta=(BindWidget))
	UButton* PrevSettingButton;

	virtual void NativeOnInitialized() override;
	
private:
	TWeakObjectPtr<USNGameSetting> Setting;

	void Init(USNGameSetting* InSetting);
	void UpdateTexts();

	UFUNCTION()
	void OnNextSetting();

	UFUNCTION()
	void OnPrevSetting();

	friend class USNVideoSettingsWidget;
};
