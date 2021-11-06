// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AssetUtils.generated.h"

/**
 * 
 */
UCLASS()
class SHPARGLEEDITOR_API UAssetUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="Shpargle|AssetUtils")
	static UBlueprint* CreateBlueprint(const FString& Path, UClass* ParentClass, TArray<UActorComponent*> InstanceComponents);

	UFUNCTION(BlueprintCallable, Category="Shpargle|AssetUtils")
	static UBlueprint* CreateActorBlueprint(const FString& Path);

};
