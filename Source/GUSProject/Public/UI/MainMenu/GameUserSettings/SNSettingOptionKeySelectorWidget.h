// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MainMenu/GameUserSettings/SNBaseSettingOptionWidget.h"
#include "SNSettingOptionKeySelectorWidget.generated.h"

class UInputKeySelector;

UCLASS()
class GUSPROJECT_API USNSettingOptionKeySelectorWidget : public USNBaseSettingOptionWidget
{
	GENERATED_BODY()

public:
	virtual void UpdateWidgetInfo() override;
	
protected:
	UPROPERTY(meta=(BindWidget))
	UInputKeySelector* FirstKeySelector;

	UPROPERTY(meta=(BindWidget))
	UInputKeySelector* SecondKeySelector;

	virtual void NativeOnInitialized() override;
	
private:
	UFUNCTION()
	void OnKeySelected(FInputChord Key);
	
	UFUNCTION()
	void OnIsSelectingKeyChanged_1();
	void OnIsSelectingKeyChanged_2();

	FInputChord LastSelectedKey;

	bool IsStartKeyChanged = false;
};
