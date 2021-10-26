// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestWindowCommands.h"

#define LOCTEXT_NAMESPACE "FTestWindowModule"

void FTestWindowCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "TestWindow", "Bring up TestWindow window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
