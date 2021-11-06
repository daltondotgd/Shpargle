// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShpargleEditor.h"
#include "ShpargleStyle.h"
#include "ShpargleCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "AssetUtils.h"
#include "EditorUtilityLibrary.h"
#include "UnrealEdMisc.h"

#define LOCTEXT_NAMESPACE "FShpargleEditorModule"

void FShpargleEditorModule::StartupModule()
{
	FShpargleStyle::Initialize();
	FShpargleStyle::ReloadTextures();

	FShpargleCommands::Register();

	ShpargleCommands = MakeShareable(new FUICommandList);

	ShpargleCommands->MapAction(
		FShpargleCommands::Get().CreateBlueprintAction,
		FExecuteAction::CreateRaw(this, &FShpargleEditorModule::CreateBlueprintActionCallback),
		FCanExecuteAction());

	ShpargleCommands->MapAction(
		FShpargleCommands::Get().RestartEditorAction,
		FExecuteAction::CreateRaw(this, &FShpargleEditorModule::RestartEditorActionCallback),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FShpargleEditorModule::RegisterMenus));
}

void FShpargleEditorModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
	FShpargleStyle::Shutdown();
	FShpargleCommands::Unregister();
}

void FShpargleEditorModule::RestartEditorActionCallback()
{
	FUnrealEdMisc::Get().RestartEditor(false);
}

void FShpargleEditorModule::CreateBlueprintActionCallback()
{
	FString Path;
	FString BlueprintName = TEXT("NewBlueprint");
	if (!UEditorUtilityLibrary::GetCurrentContentBrowserPath(Path))
	{
		Path = TEXT("/Game");
	}
	UAssetUtils::CreateActorBlueprint(Path / BlueprintName);
}

void FShpargleEditorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.File");
		{
			FToolMenuSection& Section = Menu->AddSection("Shpargle", LOCTEXT("Shpargle", "Shpargle"));
			Section.AddMenuEntryWithCommandList(FShpargleCommands::Get().RestartEditorAction, ShpargleCommands);
		}
	}

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Tools");
		{
			FToolMenuSection& Section = Menu->AddSection("Shpargle", LOCTEXT("Shpargle", "Shpargle"));
			Section.AddMenuEntryWithCommandList(FShpargleCommands::Get().CreateBlueprintAction, ShpargleCommands);
		}
	}

	{
		//UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		//{
		//	FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Shpargle");
		//	{
		//		FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FShpargleCommands::Get().CreateBlueprintAction));
		//		Entry.SetCommandList(ShpargleCommands);
		//	}
		//}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FShpargleEditorModule, ShpargleEditor)