// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestButtonCommands.h"

#define LOCTEXT_NAMESPACE "FTestButtonModule"

void FTestButtonCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "TestButton", "Execute TestButton action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
