// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SNGameSetting.generated.h"

UENUM()
enum EWidgetType
{
	Standard,
	Slider
	// maybe more in feature
};

UCLASS()
class GUSPROJECT_API USNGameSetting : public UObject
{
	GENERATED_BODY()

public:
	FText GetSettingName() const;
	FText GetSettingDescription() const;
	void SetSettingName(const FText InSettingName);
	void SetSettingDescription(const FText InSettingDescription);

	virtual void ApplyNextOption();
	virtual void ApplyPreviousOption();
	virtual FText GetCurrentOptionName() const;
	// for Resolution scale only
	virtual void SetValue(float Percent);

	EWidgetType WidgetType = EWidgetType::Standard;
	
protected:

private:
	FText SettingName;
	FText SettingDescription;
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
	void SetOptions(const TArray<FOptionNumber>& InOptions);

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

USTRUCT()
struct FOptionEnum
{
	GENERATED_BODY()

	FText DisplayValue;
	EWindowMode::Type Value;
};

UCLASS()
class USNGameSetting_Enum : public USNGameSetting
{
	GENERATED_BODY()

public:

	void AddGetterFunc(TFunction<EWindowMode::Type()> InGetterFunc);
	void AddSetterFunc(const TFunction<void(EWindowMode::Type)> InSetterFunc);
	void AddOption(FText InOptionDisplayName, EWindowMode::Type InOptionValue);
	void SetOptions(const TArray<FOptionEnum>& InOptions);

	virtual void ApplyNextOption() override;
	virtual void ApplyPreviousOption() override;
	virtual FText GetCurrentOptionName() const override;

protected:

private:
	TArray<FOptionEnum> EnumOptions;
	TFunction<EWindowMode::Type()> GetterFunc;
	TFunction<void(EWindowMode::Type)> SetterFunc;

	/*EWindowMode::Type*/int32 GetCurrentIndex() const;
	EWindowMode::Type GetCurrentValue() const;
	void SetCurrentValue(EWindowMode::Type InValue);
};

USTRUCT()
struct FOptionIntPoint
{
	GENERATED_BODY()

	FText DisplayValue;
	FIntPoint Value;
};

UCLASS()
class USNGameSetting_IntPoint : public USNGameSetting
{
	GENERATED_BODY()
	
public:
	void AddGetterFunc(TFunction<FIntPoint()> InGetterFunc);
	void AddSetterFunc(const TFunction<void(FIntPoint)> InSetterFunc);
	void AddOption(FText InOptionDisplayName, FIntPoint InOptionValue);
	void SetOptions(const TArray<FOptionIntPoint>& InOptions);

	virtual void ApplyNextOption() override;
	virtual void ApplyPreviousOption() override;
	virtual FText GetCurrentOptionName() const override;

protected:

private:
	TArray<FOptionIntPoint> IntPointOptions;
	TFunction<FIntPoint()> GetterFunc;
	TFunction<void(FIntPoint)> SetterFunc;

	int32 GetCurrentIndex() const;
	FIntPoint GetCurrentValue() const;
	void SetCurrentValue(FIntPoint InValue);
};

UCLASS()
class USNGameSetting_Float : public USNGameSetting
{
	GENERATED_BODY()

public:
	void AddGetterFunc(TFunction<float()> InGetterFunc);
	void AddSetterFunc(const TFunction<void(float)> InSetterFunc);
	float GetCurrentValue() const;
	
	// for Resolution scale only
	virtual void SetValue(float Percent);
	
protected:

private:
	TFunction<float()> GetterFunc;
	TFunction<void(float)> SetterFunc;
};

USTRUCT()
struct FOptionBool
{
	GENERATED_BODY()

	FText DisplayValue;
	bool Value;
};

UCLASS()
class USNGameSetting_Bool : public USNGameSetting
{
	GENERATED_BODY()
	
public:
	void AddGetterFunc(TFunction<bool()> InGetterFunc);
	void AddSetterFunc(const TFunction<void(bool)> InSetterFunc);
	void AddOption(FText InOptionDisplayName, bool InOptionValue);
	void SetOptions(const TArray<FOptionBool>& InOptions);

	virtual void ApplyNextOption() override;
	virtual void ApplyPreviousOption() override;
	virtual FText GetCurrentOptionName() const override;

protected:

private:
	TArray<FOptionBool> BoolOptions;
	TFunction<bool()> GetterFunc;
	TFunction<void(bool)> SetterFunc;

	int32 GetCurrentIndex() const;
	bool GetCurrentValue() const;
	void SetCurrentValue(bool InValue);
	
};