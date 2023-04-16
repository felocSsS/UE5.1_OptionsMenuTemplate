// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SNSensitivityDataAsset.generated.h"

UCLASS()
class GUSPROJECT_API USNSensitivityDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float MouseSensitivityX;

	UPROPERTY(EditAnywhere)
	float MouseSensitivityY;

	UPROPERTY(EditAnywhere)
	bool bInvertMouseX;

	UPROPERTY(EditAnywhere)
	bool bInvertMouseY;
};
