// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SNGameSetting.generated.h"

UCLASS()
class GUSPROJECT_API USNGameSetting : public UObject
{
	GENERATED_BODY()

public:
	FText GetSettingName() const;
	void SetSettingName(const FText InSettingName);

	virtual void ApplyNextOption();
	virtual void ApplyPreviousOption();
	virtual FText GetCurrentOptionName() const;
	
protected:

private:
	FText SettingName;
};

USTRUCT()
struct FOptionNumber
{
	GENERATED_BODY()

	FText DisplayValue;
	int32 Value;
};

UCLASS()
class USNGameSetting_Number : public USNGameSetting
{
	GENERATED_BODY()
	
public:
	void AddGetterFunc(TFunction<int32()> InGetterFunc);
	void AddSetterFunc(const TFunction<void(int32)> InSetterFunc);
	void AddOption(FText InOptionDisplayName, int32 InOptionValue);

	virtual void ApplyNextOption() override;
	virtual void ApplyPreviousOption() override;
	virtual FText GetCurrentOptionName() const override;

protected:

private:
	TArray<FOptionNumber> NumberOptions;
	TFunction<int32()> GetterFunc;
	TFunction<void(int32)> SetterFunc;

	int32 GetCurrentIndex() const;
	int32 GetCurrentValue() const;
	void SetCurrentValue(int32 InValue);
};
