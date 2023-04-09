// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MainMenu/GameUserSettings/SNBaseSettingOptionWidget.h"
#include "SNSettingOptionKeySelectorWidget.generated.h"

class UInputKeySelector;
class UButton;

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

	UPROPERTY(meta=(BindWidget))
	UButton* DeleteKeyButton;

	virtual void NativeOnInitialized() override;
	
private:
	UFUNCTION()
	void OnKeySelected1(FInputChord Key);
	UFUNCTION()
	void OnKeySelected2(FInputChord Key);
	UFUNCTION()
	void OnIsSelectingKeyChanged_1();
	UFUNCTION()
	void OnIsSelectingKeyChanged_2();
	UFUNCTION()
	void OnDeleteKeyButtonClick();

	void SaveKeys();

	FInputChord LastSelectedKey;
	
};
