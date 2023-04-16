// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SNGameSettingCollectionWidget.generated.h"

class UTextBlock;
class UVerticalBox;

UCLASS()
class GUSPROJECT_API USNGameSettingCollectionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetCollectionHeaderText(FText InText);
	void AddChildToContainer(UUserWidget* SettingWidget);

	TArray<UWidget*> GetChildren() const;
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> SettingCollectionHeader;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> SettingsContainer;

	virtual void NativeOnInitialized() override;
	
private:
	
};
