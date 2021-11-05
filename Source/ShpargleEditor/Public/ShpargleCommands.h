// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ShpargleStyle.h"

class FShpargleCommands : public TCommands<FShpargleCommands>
{
public:

	FShpargleCommands()
		: TCommands<FShpargleCommands>(TEXT("Shpargle"), NSLOCTEXT("Contexts", "Shpargle", "Shpargle Plugin"), NAME_None, FShpargleStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> CreateBlueprintAction;
};
