// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestButton.h"
#include "TestButtonStyle.h"
#include "TestButtonCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName TestButtonTabName("TestButton");

#define LOCTEXT_NAMESPACE "FTestButtonModule"

void FTestButtonModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FTestButtonStyle::Initialize();
	FTestButtonStyle::ReloadTextures();

	FTestButtonCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FTestButtonCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FTestButtonModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FTestButtonModule::RegisterMenus));
}

void FTestButtonModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FTestButtonStyle::Shutdown();

	FTestButtonCommands::Unregister();
}

void FTestButtonModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FTestButtonModule::PluginButtonClicked()")),
							FText::FromString(TEXT("TestButton.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FTestButtonModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Tools");
		{
			FToolMenuSection& Section = Menu->AddSection("Shpargle", LOCTEXT("Shpargle", "Shpargle"));
			Section.AddMenuEntryWithCommandList(FTestButtonCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Shpargle");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FTestButtonCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTestButtonModule, TestButton)