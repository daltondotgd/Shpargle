// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "TestButtonStyle.h"

class FTestButtonCommands : public TCommands<FTestButtonCommands>
{
public:

	FTestButtonCommands()
		: TCommands<FTestButtonCommands>(TEXT("TestButton"), NSLOCTEXT("Contexts", "TestButton", "TestButton Plugin"), NAME_None, FTestButtonStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
