// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SNGameSettingInitializer.generated.h"

class USNGameSettingCollection;

UCLASS()
class GUSPROJECT_API USNGameSettingInitializer : public UObject
{
	GENERATED_BODY()

public:
	virtual void Init();
	TArray<USNGameSettingCollection*> GetSettingCollections();
	
protected:
	TArray<USNGameSettingCollection*> SettingCollections;
	
private:
	
};

UCLASS()
class GUSPROJECT_API USNGameSettingInitializer_Video : public USNGameSettingInitializer
{
	GENERATED_BODY()

public:
	virtual void Init();
	
protected:

private:
	
};