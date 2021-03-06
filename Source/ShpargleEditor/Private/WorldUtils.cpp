// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldUtils.h"
#include "Editor.h"
#include "UnrealEd.h"
#include "EditorLevelUtils.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "WorldPartition/WorldPartition.h"
#include "LevelInstance/LevelInstanceActor.h"
#include "LevelInstance/LevelInstanceSubsystem.h"
#include "LevelInstance/Packed/PackedLevelInstanceActor.h"


UStaticMeshComponent* UWorldUtils::AddStaticMeshComponentToActor(class AActor* TargetActor, FString Name, class UStaticMesh* Mesh, const FTransform& RelativeTransform)
{
	UStaticMeshComponent* Component = NewObject<UStaticMeshComponent>(TargetActor, *Name);
	Component->ClearFlags(RF_DefaultSubObject);

	Component->SetStaticMesh(Mesh);
	Component->SetRelativeTransform_Direct(RelativeTransform);

	Component->SetupAttachment(TargetActor->GetRootComponent());
	Component->UpdateComponentToWorld();
	Component->RegisterComponent();
	Component->OnComponentCreated();

	TargetActor->AddInstanceComponent(Component);
	TargetActor->RerunConstructionScripts();

	return Component;
}


void UWorldUtils::DeleteActors(const TArray<AActor*>& Actors)
{
	GUnrealEd->DeleteActors(Actors, GEditor->GetEditorWorldContext().World(), nullptr, false, false, false);
}

UWorldPartition* UWorldUtils::GetWorldPartition()
{
	return GEditor->GetEditorWorldContext().World()->GetWorldPartition();
}

ALevelInstance* UWorldUtils::ConvertActorsToPackedLevelInstance(const TArray<AActor*>& Actors, const FString& Path)
{
	if (ULevelInstanceSubsystem* LevelInstanceSubsystem = GEditor->GetEditorWorldContext().World()->GetSubsystem<ULevelInstanceSubsystem>())
	{
		FNewLevelInstanceParams CreationParams;
		CreationParams.LevelPackageName = Path;
		CreationParams.bExternalActors = false;
		CreationParams.Type = ELevelInstanceCreationType::PackedLevelInstance;
		return LevelInstanceSubsystem->CreateLevelInstanceFrom(Actors, CreationParams);
	}

	return nullptr;
}

bool UWorldUtils::MoveActorsToLevel(class ALevelInstance* LevelInstanceActor, const TArray<AActor*>& ActorsToMove)
{
	if (ULevelInstanceSubsystem* LevelInstanceSubsystem = GEditor->GetEditorWorldContext().World()->GetSubsystem<ULevelInstanceSubsystem>())
	{
		LevelInstanceSubsystem->EditLevelInstance(LevelInstanceActor);

		bool Result = LevelInstanceSubsystem->MoveActorsTo(LevelInstanceActor, ActorsToMove);
		LevelInstanceSubsystem->CommitLevelInstance(LevelInstanceActor, /* bDiscardEdits = */ false, /* bPromptForSave = */ false);
		return Result;
	}

	return false;
}

TArray<AActor*> UWorldUtils::BreakLevelInstance(ALevelInstance* LevelInstanceActor, int32 Levels)
{
	TArray<AActor*> MovedActors = TArray<AActor*>();

	if (ULevelInstanceSubsystem* LevelInstanceSubsystem = GEditor->GetEditorWorldContext().World()->GetSubsystem<ULevelInstanceSubsystem>())
	{
		LevelInstanceSubsystem->BreakLevelInstance(LevelInstanceActor, Levels, &MovedActors);
	}

	return MovedActors;
}

/**
 * Exactly what the Load Selected Cells does in the World Partition window.
 */
void UWorldUtils::LoadWorldPartitionCell(const FBox& SelectedBox)
{
	if (UWorldPartition* WorldPartition = GetWorldPartition())
	{
		WorldPartition->LoadEditorCells(SelectedBox, true);
		GEditor->RedrawLevelEditingViewports();
	}
}

/**
 * Exactly what the Unload Selected Cells does in the World Partition window.
 */
void UWorldUtils::UnloadWorldPartitionCell(const FBox& SelectedBox)
{
	if (UWorldPartition* WorldPartition = GetWorldPartition())
	{
		WorldPartition->UnloadEditorCells(SelectedBox, true);
		GEditor->RedrawLevelEditingViewports();
	}
}

/**
 * Skips calling redraw on the level viewports.
 */
void UWorldUtils::LoadWorldPartitionCellLight(const FBox& SelectedBox)
{
	if (UWorldPartition* WorldPartition = GetWorldPartition())
	{
		WorldPartition->LoadEditorCells(SelectedBox, true);
	}
}

/**
 * Skips calling redraw on the level viewports.
 */
void UWorldUtils::UnloadWorldPartitionCellLight(const FBox& SelectedBox)
{
	if (UWorldPartition* WorldPartition = GetWorldPartition())
	{
		WorldPartition->UnloadEditorCells(SelectedBox, true);
	}
}

/**
 * Skips calling redraw on the level viewports and uses the World Partition pointer delivered by user.
 * The responsibility for delivering the right pointer is transfered to the user, so we can skip the check.
 */
void UWorldUtils::LoadWorldPartitionCellSuperlight(UWorldPartition* WorldPartition, const FBox& SelectedBox)
{
	WorldPartition->LoadEditorCells(SelectedBox, true);
}

/**
 * Skips calling redraw on the level viewports and uses the World Partition pointer delivered by user.
 * The responsibility for delivering the right pointer is transfered to the user, so we can skip the check.
 */
void UWorldUtils::UnloadWorldPartitionCellSuperlight(UWorldPartition* WorldPartition, const FBox& SelectedBox)
{
	WorldPartition->UnloadEditorCells(SelectedBox, true);
}
