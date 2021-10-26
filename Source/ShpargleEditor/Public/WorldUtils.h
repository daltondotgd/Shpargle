// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WorldUtils.generated.h"

/**
 * 
 */
UCLASS()
class SHPARGLEEDITOR_API UWorldUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "World Utils")
	static class UStaticMeshComponent* AddStaticMeshComponentToActor(class AActor* TargetActor, FString Name, class UStaticMesh* Mesh, const FTransform& RelativeTransform);

};
