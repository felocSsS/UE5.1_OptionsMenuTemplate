// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SNBaseSettingWidget.h"
#include "SNSettingOption_SliderWidget.generated.h"

class USlider;
class UTextBlock;

UCLASS()
class GUSPROJECT_API USNSettingOption_SliderWidget : public USNBaseSettingWidget
{
	GENERATED_BODY()

public:
	virtual void UpdateWidgetInfo() override;
	
protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* SettingDisplayName;
	
	UPROPERTY(meta=(BindWidget))
	USlider* ProgressSlider;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnSliderValueChanged(float Value);
};
