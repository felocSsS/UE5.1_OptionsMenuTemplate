// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SNBaseSettingsScreenWidget.generated.h"

class UVerticalBox;
class UTextBlock;
class USNGameSettingCollectionWidget;
class USNBaseGameSettingWidget;
class USNGameSettingInitializer;
class UButton;
class USNBaseSettingOptionWidget;

UCLASS()
class GUSPROJECT_API USNBaseSettingsScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<USNGameSettingCollectionWidget> GameSettingCollectionWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<USNBaseSettingOptionWidget> GameSettingButtonWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<USNBaseSettingOptionWidget> GameSettingSliderWidgetClass;

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* SettingsCollectionContainer;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* DescriptionHeader;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* DescriptionText;
	
	virtual void NativeOnInitialized() override;

	UPROPERTY()
	USNGameSettingInitializer* GameSettingInitializer;
	
private:
	
};

UCLASS()
class GUSPROJECT_API USNSettingsScreenWidget_Video : public USNBaseSettingsScreenWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UButton* RunBenchmarkButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnBenchmark();
	
	void OnVideoSettingsUpdated();
};

UCLASS()
class GUSPROJECT_API USNSettingsScreenWidget_Audio : public USNBaseSettingsScreenWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	
};

UCLASS()
class GUSPROJECT_API USNSettingsScreenWidget_Gameplay : public USNBaseSettingsScreenWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	
};

UCLASS()
class GUSPROJECT_API USNSettingsScreenWidget_MouseAndKeyboard : public USNBaseSettingsScreenWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	
};
