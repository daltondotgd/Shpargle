// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestEditorModeEditorModeToolkit.h"
#include "TestEditorModeEditorMode.h"
#include "Engine/Selection.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "TestEditorModeEditorModeToolkit"

FTestEditorModeEditorModeToolkit::FTestEditorModeEditorModeToolkit()
{
}

void FTestEditorModeEditorModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode)
{
	FModeToolkit::Init(InitToolkitHost, InOwningMode);
}

void FTestEditorModeEditorModeToolkit::GetToolPaletteNames(TArray<FName>& PaletteNames) const
{
	PaletteNames.Add(NAME_Default);
}


FName FTestEditorModeEditorModeToolkit::GetToolkitFName() const
{
	return FName("TestEditorModeEditorMode");
}

FText FTestEditorModeEditorModeToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("DisplayName", "TestEditorModeEditorMode Toolkit");
}

#undef LOCTEXT_NAMESPACE
