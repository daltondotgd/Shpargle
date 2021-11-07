// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FShpargleEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void RestartEditorActionCallback();
	void CreateBlueprintActionCallback();

private:
	void RegisterMenus();


private:
	TSharedPtr<class FUICommandList> ShpargleCommands;

};
