// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SNBaseSettingOptionWidget.generated.h"

class USNGameSetting;
class UTextBlock;

UCLASS()
class GUSPROJECT_API USNBaseSettingOptionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void UpdateWidgetInfo();
	
protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* SettingDisplayName;
	
	TWeakObjectPtr<USNGameSetting> Setting;
	
	virtual void Init(USNGameSetting* InSetting);
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
private:
	TFunction<void(FText, FText)> SetDescriptionBlockTextFunc;
	friend class USNBaseSettingsScreenWidget;
	
};
