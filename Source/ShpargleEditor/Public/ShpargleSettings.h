// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ShpargleSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Shpargle)
class SHPARGLEEDITOR_API UShpargleSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category="Shpargle")
	bool bEnableExperimentalTools = false;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category="Shpargle")
	bool bEnableTestTools = false;

	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;

};
