// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SNBaseSettingOptionWidget.generated.h"

class USNGameSetting;

UCLASS()
class GUSPROJECT_API USNBaseSettingOptionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void UpdateWidgetInfo();
	
protected:
	TWeakObjectPtr<USNGameSetting> Setting;
	
	virtual void Init(USNGameSetting* InSetting);
	
private:
	friend class USNBaseSettingsScreenWidget;
	
};
