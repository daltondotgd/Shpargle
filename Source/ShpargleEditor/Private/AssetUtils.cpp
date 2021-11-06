// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetUtils.h"
#include "AssetToolsModule.h"
#include "AssetRegistryModule.h"
#include "Engine/SimpleConstructionScript.h"
#include "Kismet2/KismetEditorUtilities.h"

#define LOCTEXT_NAMESPACE "UAssetUtils"

UPackage* CreateBlueprintPackage(const FString& Path, FString& OutAssetName)
{
	FString PackageName;
	if (FPackageName::IsValidTextForLongPackageName(Path))
	{
		OutAssetName = FPackageName::GetLongPackageAssetName(Path);
	}

	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");

	if (OutAssetName.Len() == 0)
	{
		PackageName = FPackageName::GetLongPackagePath(Path);
		FString BasePath = PackageName + TEXT("/") + LOCTEXT("BlueprintName_Default", "NewBlueprint").ToString();
		AssetToolsModule.Get().CreateUniqueAssetName(BasePath, FString(), PackageName, OutAssetName);
	}
	else
	{
		PackageName = FPackageName::GetLongPackagePath(Path);
		AssetToolsModule.Get().CreateUniqueAssetName(PackageName / OutAssetName, FString(), PackageName, OutAssetName);
	}

	return CreatePackage(*PackageName);
}

UBlueprint* UAssetUtils::CreateBlueprint(const FString& Path, UClass* ParentClass, TArray<UActorComponent*> InstanceComponents)
{
	UBlueprint* NewBlueprint = nullptr;
	FString BlueprintName;

	if (UPackage* Outer = CreateBlueprintPackage(Path, BlueprintName))
	{
		if (Outer != nullptr)
		{
			NewBlueprint = FKismetEditorUtilities::CreateBlueprint(ParentClass, Outer, FName(*BlueprintName), EBlueprintType::BPTYPE_Normal, UBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), FName("CreateFromEditorScript"));
		}

		if (NewBlueprint != nullptr)
		{
			FAssetRegistryModule::AssetCreated(NewBlueprint);
			Outer->MarkPackageDirty();

			// InstanceComponents.Add(...);

			FKismetEditorUtilities::FAddComponentsToBlueprintParams AddCompParams;
			AddCompParams.OptionalNewRootNode = NewBlueprint->SimpleConstructionScript->GetDefaultSceneRootNode();
			FKismetEditorUtilities::AddComponentsToBlueprint(NewBlueprint, InstanceComponents, AddCompParams);

			// AActor* CDO = CastChecked<AActor>(NewBlueprint->GeneratedClass->GetDefaultObject());

			FKismetEditorUtilities::CompileBlueprint(NewBlueprint);
		}
	}

	return NewBlueprint;
}

UBlueprint* UAssetUtils::CreateActorBlueprint(const FString& Path)
{
	return CreateBlueprint(Path, AActor::StaticClass(), TArray<UActorComponent*>());
}

#undef LOCTEXT_NAMESPACE