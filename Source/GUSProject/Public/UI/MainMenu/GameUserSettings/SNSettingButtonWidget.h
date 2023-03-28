// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SNSettingButtonWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class GUSPROJECT_API USNSettingButtonWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetIndex(int32 Index);
	void SetButtonText(FText InText);
	void SetOpenWidgetFunc(TFunction<void(int32)> InFunc);
	
protected:
	virtual void NativeOnInitialized() override;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ButtonText;

	UPROPERTY(meta=(BindWidget))
	UButton* SettingButton;
	
private:
	int32 IndexOfSettings;
	TFunction<void(int32)> OpenWidgetFunc;

	UFUNCTION()
	void OnSettingButtonClicked();
};
