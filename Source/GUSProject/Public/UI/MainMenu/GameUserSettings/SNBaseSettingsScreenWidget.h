// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SNBaseSettingsScreenWidget.generated.h"

class USNSensitivityDataAsset;
class UVerticalBox;
class UTextBlock;
class USNGameSettingCollectionWidget;
class USNBaseGameSettingWidget;
class USNGameSettingInitializer;
class UButton;
class USNBaseSettingOptionWidget;

UCLASS(Abstract)
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<USNBaseSettingOptionWidget> GameSettingKeySelectorWidgetClass;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> SettingsCollectionContainer;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> DescriptionHeader;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> DescriptionText;
	
	virtual void NativeOnInitialized() override;

	UPROPERTY()
	TObjectPtr<USNGameSettingInitializer> GameSettingInitializer;
	
private:
	void SetDescriptionBlockText(FText InDescriptionHeaderText, FText InDescriptionText);
	
};

UCLASS()
class GUSPROJECT_API USNSettingsScreenWidget_Video : public USNBaseSettingsScreenWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> RunBenchmarkButton;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USNSensitivityDataAsset> SensitivityDataAsset;
	
};
