// Fill out your copyright notice in the Description page of Project Settings.

#include "GameSettings/SNGameSetting.h"

FText USNGameSetting::GetSettingName() const
{
	return SettingName;
}

FText USNGameSetting::GetSettingDescription() const
{
	return SettingDescription;
}

void USNGameSetting::SetSettingName(const FText InSettingName)
{
	SettingName = InSettingName;
}

void USNGameSetting::SetSettingDescription(const FText InSettingDescription)
{
	SettingDescription = InSettingDescription;
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

void USNGameSetting::SetValue(float Percent)
{
}

void USNGameSetting::SetValue(FName ActionName, FSelectedKeys_Action Keys)
{
}

FSelectedKeys_Action USNGameSetting::GetSelectedKeys() const
{
	return FSelectedKeys_Action{};
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
	return NumberOptions.IndexOfByPredicate([&](const FOptionNumber& Opt){ return CurrentValue == Opt.Value; });
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

/*
 *  USNGameSetting_Enum cpp
 */
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

int32 USNGameSetting_Enum::GetCurrentIndex() const
{
	const EWindowMode::Type CurrentValue = GetCurrentValue();
	/*const int32 Index =*/ return EnumOptions.IndexOfByPredicate([&](const FOptionEnum& Opt){ return CurrentValue == Opt.Value; });
	/*return EnumOptions[Index].Value;*/
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

/*
 *  USNGameSetting_IntPoint cpp
 */

void USNGameSetting_IntPoint::AddGetterFunc(TFunction<FIntPoint()> InGetterFunc)
{
	GetterFunc = InGetterFunc;
}

void USNGameSetting_IntPoint::AddSetterFunc(const TFunction<void(FIntPoint)> InSetterFunc)
{
	SetterFunc = InSetterFunc;
}

void USNGameSetting_IntPoint::AddOption(FText InOptionDisplayName, FIntPoint InOptionValue)
{
	IntPointOptions.Add(FOptionIntPoint{InOptionDisplayName, InOptionValue});
}

void USNGameSetting_IntPoint::SetOptions(const TArray<FOptionIntPoint>& InOptions)
{
	IntPointOptions = InOptions;
}

void USNGameSetting_IntPoint::ApplyNextOption()
{
	const int32 CurrentIndex = GetCurrentIndex();
	if (CurrentIndex == INDEX_NONE) return;
	
	const int32 NextIndex = (CurrentIndex + 1) % IntPointOptions.Num();
	SetCurrentValue(IntPointOptions[NextIndex].Value);
}

void USNGameSetting_IntPoint::ApplyPreviousOption()
{
	const int32 CurrentIndex = GetCurrentIndex();
	if (CurrentIndex == INDEX_NONE) return;
	
	const int32 PreviousIndex = CurrentIndex == 0 ? IntPointOptions.Num() - 1 : CurrentIndex - 1;
	SetCurrentValue(IntPointOptions[PreviousIndex].Value);
}

FText USNGameSetting_IntPoint::GetCurrentOptionName() const
{
	const FIntPoint CurrentValue = GetCurrentValue();
	const auto Option = IntPointOptions.FindByPredicate([&](const FOptionIntPoint& Opt) { return CurrentValue == Opt.Value;} );
	if (!Option) return FText();
	return Option->DisplayValue;
}

int32 USNGameSetting_IntPoint::GetCurrentIndex() const
{
	const FIntPoint CurrentValue = GetCurrentValue();
	return IntPointOptions.IndexOfByPredicate([&](const FOptionIntPoint& Opt){ return CurrentValue == Opt.Value; });
}

FIntPoint USNGameSetting_IntPoint::GetCurrentValue() const
{
	if (!GetterFunc) return FIntPoint();

	return GetterFunc();
}

void USNGameSetting_IntPoint::SetCurrentValue(FIntPoint InValue)
{
	if (!SetterFunc) return;

	SetterFunc(InValue);
}

/*
 *  USNGameSetting_float cpp
 */

void USNGameSetting_Float::AddGetterFunc(TFunction<float()> InGetterFunc)
{
	GetterFunc = InGetterFunc;
}

void USNGameSetting_Float::AddSetterFunc(const TFunction<void(float)> InSetterFunc)
{
	SetterFunc = InSetterFunc;
}

float USNGameSetting_Float::GetCurrentValue() const
{
	if (!GetterFunc) return 0.0f;

	return GetterFunc();
}

void USNGameSetting_Float::SetValue(float Percent)
{
	SetterFunc(Percent);
}

/*
 *  USNGameSetting_bool cpp
 */

void USNGameSetting_Bool::AddGetterFunc(TFunction<bool()> InGetterFunc)
{
	GetterFunc = InGetterFunc;
}

void USNGameSetting_Bool::AddSetterFunc(const TFunction<void(bool)> InSetterFunc)
{
	SetterFunc = InSetterFunc;
}

void USNGameSetting_Bool::AddOption(FText InOptionDisplayName, bool InOptionValue)
{
	BoolOptions.Add(FOptionBool{InOptionDisplayName, InOptionValue});
}

void USNGameSetting_Bool::SetOptions(const TArray<FOptionBool>& InOptions)
{
	BoolOptions = InOptions;
}

void USNGameSetting_Bool::ApplyNextOption()
{
	const int32 CurrentIndex = GetCurrentIndex();
	if (CurrentIndex == INDEX_NONE) return;
	
	const int32 NextIndex = (CurrentIndex + 1) % BoolOptions.Num();
	SetCurrentValue(BoolOptions[NextIndex].Value);
}

void USNGameSetting_Bool::ApplyPreviousOption()
{
	const int32 CurrentIndex = GetCurrentIndex();
	if (CurrentIndex == INDEX_NONE) return;
	
	const int32 PreviousIndex = CurrentIndex == 0 ? BoolOptions.Num() - 1 : CurrentIndex - 1;
	SetCurrentValue(BoolOptions[PreviousIndex].Value);
}

FText USNGameSetting_Bool::GetCurrentOptionName() const
{
	const FIntPoint CurrentValue = GetCurrentValue();
	const auto Option = BoolOptions.FindByPredicate([&](const FOptionBool& Opt) { return CurrentValue == Opt.Value;} );
	if (!Option) return FText();
	return Option->DisplayValue;
}

int32 USNGameSetting_Bool::GetCurrentIndex() const
{
	const bool CurrentValue = GetCurrentValue();
	return BoolOptions.IndexOfByPredicate([&](const FOptionBool& Opt){ return CurrentValue == Opt.Value; });
}

bool USNGameSetting_Bool::GetCurrentValue() const
{
	if (!GetterFunc) return false;

	return GetterFunc();
}

void USNGameSetting_Bool::SetCurrentValue(bool InValue)
{
	if (!SetterFunc) return;

	SetterFunc(InValue);
}

/*
 *  USNGameSetting_KeySelector_Base cpp
 */

void USNGameSetting_KeySelector_Base::SetActionOrAxisName(FName InName)
{
	ActionOrAxisName = InName;
}

void USNGameSetting_KeySelector_Base::SetInputType(EInputType InInputType)
{
	InputType = InInputType;
}

EInputType USNGameSetting_KeySelector_Base::GetInputType() const
{
	return InputType;
}

FName USNGameSetting_KeySelector_Base::GetActionOrAxisName() const
{
	return ActionOrAxisName;
}

/*
 *  USNGameSetting_KeySelector_Action cpp
 */

void USNGameSetting_KeySelector_Action::AddGetterFunc(TFunction<FSelectedKeys_Action(FName)> InGetterFunc)
{
	GetterFunc = InGetterFunc;
}

void USNGameSetting_KeySelector_Action::AddSetterFunc(const TFunction<void(FName, FSelectedKeys_Action)> InSetterFunc)
{
	SetterFunc = InSetterFunc;
}

FSelectedKeys_Action USNGameSetting_KeySelector_Action::GetSelectedKeys() const
{
	if (!GetterFunc) return FSelectedKeys_Action{};

	return GetterFunc(ActionOrAxisName);
}

void USNGameSetting_KeySelector_Action::SetValue(FName ActionName, FSelectedKeys_Action Keys)
{
	if (SetterFunc) SetterFunc(ActionName, Keys);
}
