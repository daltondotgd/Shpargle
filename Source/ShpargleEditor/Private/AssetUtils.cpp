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

	// If no AssetName was found, generate a unique asset name.
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

UBlueprint* UAssetUtils::CreateBlueprint(const FString& Path, UClass* ParentClass)
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
			// Notify the asset registry
			FAssetRegistryModule::AssetCreated(NewBlueprint);

			// Mark the package dirty
			Outer->MarkPackageDirty();


			USCS_Node* DefaultSceneRoot = NewBlueprint->SimpleConstructionScript->GetDefaultSceneRootNode();
			TArray<UActorComponent*> InstanceComponents;
			//InstanceComponents.Add(DefaultSceneRoot);  // not sure yet

			FKismetEditorUtilities::FAddComponentsToBlueprintParams AddCompParams;
			AddCompParams.OptionalNewRootNode = DefaultSceneRoot;
			FKismetEditorUtilities::AddComponentsToBlueprint(NewBlueprint, InstanceComponents, AddCompParams);

			// AActor* CDO = CastChecked<AActor>(NewBlueprint->GeneratedClass->GetDefaultObject());

			FKismetEditorUtilities::CompileBlueprint(NewBlueprint);
		}
	}

	return NewBlueprint;
}

UBlueprint* UAssetUtils::CreateActorBlueprint(const FString& Path)
{
	return CreateBlueprint(Path, AActor::StaticClass());
}

#undef LOCTEXT_NAMESPACE