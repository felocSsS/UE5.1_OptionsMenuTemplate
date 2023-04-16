// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SNGameUserSettingsWidget.generated.h"

class UHorizontalBox;
class USNBaseSettingsScreenWidget;
class USNSettingButtonWidget;
class UWidgetSwitcher;

UCLASS()
class GUSPROJECT_API USNGameUserSettingsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	TMap<TSubclassOf<USNBaseSettingsScreenWidget>, FText> SettingsScreenWidgetClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	TSubclassOf<USNSettingButtonWidget> SettingsScreenButtonWidgetClass;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UHorizontalBox> ButtonsContainer;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> SettingsContainer;

private:
	void OpenWidget(int32 Index);
	
};