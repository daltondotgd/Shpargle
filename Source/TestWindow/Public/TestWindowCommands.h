// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "TestWindowStyle.h"

class FTestWindowCommands : public TCommands<FTestWindowCommands>
{
public:

	FTestWindowCommands()
		: TCommands<FTestWindowCommands>(TEXT("TestWindow"), NSLOCTEXT("Contexts", "TestWindow", "TestWindow Plugin"), NAME_None, FTestWindowStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};