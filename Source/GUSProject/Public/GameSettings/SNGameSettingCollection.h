// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SNGameSettingCollection.generated.h"

class USNGameSetting;

UCLASS()
class GUSPROJECT_API USNGameSettingCollection : public UObject
{
	GENERATED_BODY()

public:
	void SetCollectionName(FText InName);
	void AddSettingToCollection(USNGameSetting* Setting);
	TArray<USNGameSetting*> GetSettings() const;
	FText GetCollectionName() const;
	
protected:

private:
	FText CollectionName;
	UPROPERTY()
	TArray<TObjectPtr<USNGameSetting>> Settings;
};
