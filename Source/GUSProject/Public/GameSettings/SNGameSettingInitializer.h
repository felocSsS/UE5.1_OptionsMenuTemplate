// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSettings/SNGameSetting.h"
#include "UObject/NoExportTypes.h"
#include "SNGameSettingInitializer.generated.h"

class USNGameSettingCollection;
class USNSensitivityDataAsset;

UCLASS(Abstract)
class GUSPROJECT_API USNGameSettingInitializer : public UObject
{
	GENERATED_BODY()

public:
	virtual void Init();
	TArray<USNGameSettingCollection*> GetSettingCollections();
	
protected:
	UPROPERTY()
	TArray<TObjectPtr<USNGameSettingCollection>> SettingCollections;
	
private:
	
};

UCLASS()
class GUSPROJECT_API USNGameSettingInitializer_Gameplay : public USNGameSettingInitializer
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	
protected:

private:
	FString GetLanguage() const;
	void SetLanguage(const FString LanguageKey);
	
};

UCLASS()
class GUSPROJECT_API USNGameSettingInitializer_Video : public USNGameSettingInitializer
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	
protected:

private:
	
};

UCLASS()
class GUSPROJECT_API USNGameSettingInitializer_MouseAndKeyboard : public USNGameSettingInitializer
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	void SetSensitivityDataAsset(USNSensitivityDataAsset* DataAsset);
	
protected:
	
private:
	float GetMouseSensitivityX() const;
	void SetMouseSensitivityX(float InMouseSensitivityX);

	float GetMouseSensitivityY() const;
	void SetMouseSensitivityY(float InMouseSensitivityY);

	bool GetMouseInvertX() const;
	void SetMouseInvertX(bool InMouseInvertX);

	bool GetMouseInvertY() const;
	void SetMouseInvertY(bool InMouseInvertY);
	
	FSelectedKeys GetSelectedKeys_Action(FName ActionName) const;
	void SetKeys_Action(FName InActionName, FSelectedKeys Keys);

	FSelectedKeys GetSelectedKeys_Axis(FName ActionName) const;
	void SetKeys_Axis(FName InActionName, FSelectedKeys Keys, float Scale);

	UPROPERTY()
	TObjectPtr<USNSensitivityDataAsset> SensitivityDataAsset;
};