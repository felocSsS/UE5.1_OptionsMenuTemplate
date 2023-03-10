// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SNVideoSettingsWidget.generated.h"

class UVerticalBox;
class USNSettingOptionWidget;
class USNSettingOption_SliderWidget;
class UButton;

UCLASS()
class GUSPROJECT_API USNVideoSettingsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
protected:
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* VideoSettingsContainer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	TSubclassOf<USNSettingOptionWidget> SettingOptionWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	TSubclassOf<USNSettingOption_SliderWidget> SettingOption_SliderWidgetClass;

	UPROPERTY(meta=(BindWidget))
	UButton* RunBenchmarkButton;

	virtual void NativeOnInitialized() override;
	
private:
	UFUNCTION()
	void OnBenchmark();
	
	void OnVideoSettingsUpdated();
	
};
