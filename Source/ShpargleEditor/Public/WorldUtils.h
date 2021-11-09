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
	UFUNCTION(BlueprintCallable, Category = "Shpargle|World Utils")
	static class UStaticMeshComponent* AddStaticMeshComponentToActor(class AActor* TargetActor, FString Name, class UStaticMesh* Mesh, const FTransform& RelativeTransform);
	
	UFUNCTION(BlueprintCallable, Category = "Shpargle|World Utils")
	static class UWorldPartition* GetWorldPartition();
	
	UFUNCTION(BlueprintCallable, Category = "Shpargle|World Utils")
	static void LoadWorldPartitionCell(const FBox& SelectedBox);
	
	UFUNCTION(BlueprintCallable, Category = "Shpargle|World Utils")
	static void UnloadWorldPartitionCell(const FBox& SelectedBox);

	UFUNCTION(BlueprintCallable, Category = "Shpargle|World Utils")
	static void LoadWorldPartitionCellLight(const FBox& SelectedBox);
	
	UFUNCTION(BlueprintCallable, Category = "Shpargle|World Utils")
	static void UnloadWorldPartitionCellLight(const FBox& SelectedBox);
	
	UFUNCTION(BlueprintCallable, Category = "Shpargle|World Utils")
	static void LoadWorldPartitionCellSuperlight(class UWorldPartition* WorldPartition, const FBox& SelectedBox);
	
	UFUNCTION(BlueprintCallable, Category = "Shpargle|World Utils")
	static void UnloadWorldPartitionCellSuperlight(class UWorldPartition* WorldPartition, const FBox& SelectedBox);

};
