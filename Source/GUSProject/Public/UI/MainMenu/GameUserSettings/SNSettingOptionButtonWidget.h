// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MainMenu/GameUserSettings/SNBaseSettingOptionWidget.h"
#include "SNSettingOptionButtonWidget.generated.h"

class UTextBlock;
class USNGameSetting;
class UButton;

UCLASS()
class GUSPROJECT_API USNSettingOptionButtonWidget : public USNBaseSettingOptionWidget
{
	GENERATED_BODY()

public:
	virtual void UpdateWidgetInfo() override;
	
protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* SettingCurrentValue;

	UPROPERTY(meta=(BindWidget))
	UButton* NextSettingButton;

	UPROPERTY(meta=(BindWidget))
	UButton* PrevSettingButton;

	virtual void NativeOnInitialized() override;
	
private:
	UFUNCTION()
	void OnNextSetting();

	UFUNCTION()
	void OnPrevSetting();
};
