// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MainMenu/GameUserSettings/SNBaseSettingOptionWidget.h"
#include "SNSettingOptionSliderWidget.generated.h"

class USlider;
class UTextBlock;

UCLASS()
class GUSPROJECT_API USNSettingOptionSliderWidget : public USNBaseSettingOptionWidget
{
	GENERATED_BODY()

public:
	virtual void UpdateWidgetInfo() override;
	virtual void Init(USNGameSetting* InSetting) override;
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USlider> ProgressSlider;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnSliderValueChanged(float Value);
};
