// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShpargleCommands.h"

#define LOCTEXT_NAMESPACE "FShpargleModule"

void FShpargleCommands::RegisterCommands()
{
	UI_COMMAND(RestartEditorAction, "Restart Editor", "Reopen the editor with the current project.", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(CreateBlueprintAction, "Create Blueprint", "Create empty, Actor-based Blueprint.", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
