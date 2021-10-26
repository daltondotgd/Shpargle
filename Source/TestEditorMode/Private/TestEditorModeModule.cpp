// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestEditorModeModule.h"
#include "TestEditorModeEditorModeCommands.h"

#define LOCTEXT_NAMESPACE "TestEditorModeModule"

void FTestEditorModeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FTestEditorModeEditorModeCommands::Register();
}

void FTestEditorModeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	FTestEditorModeEditorModeCommands::Unregister();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FTestEditorModeModule, TestEditorModeEditorMode)