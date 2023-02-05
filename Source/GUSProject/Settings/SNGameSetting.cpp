// Fill out your copyright notice in the Description page of Project Settings.

#include "Settings/SNGameSetting.h"

FText USNGameSetting::GetSettingName() const
{
	return SettingName;
}

void USNGameSetting::SetSettingName(const FText InSettingName)
{
	SettingName = InSettingName;
}

void USNGameSetting::ApplyNextOption()
{
}

void USNGameSetting::ApplyPreviousOption()
{
}

FText USNGameSetting::GetCurrentOptionName() const
{
	return FText();
}

/*
 *  USNGameSetting_Number cpp
 */

void USNGameSetting_Number::AddGetterFunc(TFunction<int32()> InGetterFunc)
{
	GetterFunc = InGetterFunc;
}

void USNGameSetting_Number::AddSetterFunc(const TFunction<void(int32)> InSetterFunc)
{
	SetterFunc = InSetterFunc;
}

void USNGameSetting_Number::AddOption(FText InOptionDisplayName, int32 InOptionValue)
{
	NumberOptions.Add(FOptionNumber{InOptionDisplayName, InOptionValue});
}

void USNGameSetting_Number::SetOptions(const TArray<FOptionNumber>& InOptions)
{
	NumberOptions = InOptions;
}

void USNGameSetting_Number::ApplyNextOption()
{
	const int32 CurrentIndex = GetCurrentIndex();
	if (CurrentIndex == INDEX_NONE) return;

	const int32 NextIndex = (CurrentIndex + 1) % NumberOptions.Num();
	SetCurrentValue(NumberOptions[NextIndex].Value);
}

void USNGameSetting_Number::ApplyPreviousOption()
{
	const int32 CurrentIndex = GetCurrentIndex();
	if (CurrentIndex == INDEX_NONE) return;

	const int32 PreviousIndex = CurrentIndex == 0 ? NumberOptions.Num() - 1 : CurrentIndex - 1;
	SetCurrentValue(NumberOptions[PreviousIndex].Value);
}

FText USNGameSetting_Number::GetCurrentOptionName() const
{
	const int32 CurrentValue = GetCurrentValue();
	const auto Option = NumberOptions.FindByPredicate([&](const FOptionNumber& Opt) { return CurrentValue == Opt.Value;} );
	if (!Option) return FText();
	return Option->DisplayValue;
}

int32 USNGameSetting_Number::GetCurrentIndex() const
{
	const int32 CurrentValue = GetCurrentValue();
	return NumberOptions.IndexOfByPredicate([&](const auto& Opt){ return CurrentValue == Opt.Value; });
}

int32 USNGameSetting_Number::GetCurrentValue() const
{
	if (!GetterFunc) return INDEX_NONE;

	return GetterFunc();
}

void USNGameSetting_Number::SetCurrentValue(int32 InValue)
{
	if (!SetterFunc) return;

	SetterFunc(InValue);
}

void USNGameSetting_Enum::AddGetterFunc(TFunction<EWindowMode::Type()> InGetterFunc)
{
	GetterFunc = InGetterFunc;
}

void USNGameSetting_Enum::AddSetterFunc(const TFunction<void(EWindowMode::Type)> InSetterFunc)
{
	SetterFunc = InSetterFunc;
}

void USNGameSetting_Enum::AddOption(FText InOptionDisplayName, EWindowMode::Type InOptionValue)
{
	EnumOptions.Add(FOptionEnum{InOptionDisplayName, InOptionValue});
}

void USNGameSetting_Enum::SetOptions(const TArray<FOptionEnum>& InOptions)
{
	EnumOptions = InOptions;
}

void USNGameSetting_Enum::ApplyNextOption()
{
	const int32 CurrentIndex = GetCurrentIndex();
	if (CurrentIndex == INDEX_NONE) return;
	
	const int32 NextIndex = (CurrentIndex + 1) % EnumOptions.Num();
	SetCurrentValue(EnumOptions[NextIndex].Value);
}

void USNGameSetting_Enum::ApplyPreviousOption()
{
	const int32 CurrentIndex = GetCurrentIndex();
	if (CurrentIndex == INDEX_NONE) return;
	
	const int32 PreviousIndex = CurrentIndex == 0 ? EnumOptions.Num() - 1 : CurrentIndex - 1;
	SetCurrentValue(EnumOptions[PreviousIndex].Value);
}

FText USNGameSetting_Enum::GetCurrentOptionName() const
{
	const EWindowMode::Type CurrentValue = GetCurrentValue();
	const auto Option = EnumOptions.FindByPredicate([&](const FOptionEnum& Opt) { return CurrentValue == Opt.Value;} );
	if (!Option) return FText();
	return Option->DisplayValue;
}

EWindowMode::Type USNGameSetting_Enum::GetCurrentIndex() const
{
	const EWindowMode::Type CurrentValue = GetCurrentValue();
	const int32 Index = EnumOptions.IndexOfByPredicate([&](const FOptionEnum& Opt){ return CurrentValue == Opt.Value; });
	return EnumOptions[Index].Value;
}

EWindowMode::Type USNGameSetting_Enum::GetCurrentValue() const
{
	if (!GetterFunc) return EWindowMode::Fullscreen;

	return GetterFunc();
}

void USNGameSetting_Enum::SetCurrentValue(EWindowMode::Type InValue)
{
	if (!SetterFunc) return;

	SetterFunc(InValue);
}
