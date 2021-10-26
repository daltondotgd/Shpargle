// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestEditorModeEditorMode.h"
#include "TestEditorModeEditorModeToolkit.h"
#include "EdModeInteractiveToolsContext.h"
#include "InteractiveToolManager.h"
#include "TestEditorModeEditorModeCommands.h"


//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
// AddYourTool Step 1 - include the header file for your Tools here
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
#include "Tools/TestEditorModeSimpleTool.h"
#include "Tools/TestEditorModeInteractiveTool.h"

// step 2: register a ToolBuilder in FTestEditorModeEditorMode::Enter() below


#define LOCTEXT_NAMESPACE "TestEditorModeEditorMode"

const FEditorModeID UTestEditorModeEditorMode::EM_TestEditorModeEditorModeId = TEXT("EM_TestEditorModeEditorMode");

FString UTestEditorModeEditorMode::SimpleToolName = TEXT("TestEditorMode_ActorInfoTool");
FString UTestEditorModeEditorMode::InteractiveToolName = TEXT("TestEditorMode_MeasureDistanceTool");


UTestEditorModeEditorMode::UTestEditorModeEditorMode()
{
	FModuleManager::Get().LoadModule("EditorStyle");

	// appearance and icon in the editing mode ribbon can be customized here
	Info = FEditorModeInfo(UTestEditorModeEditorMode::EM_TestEditorModeEditorModeId,
		LOCTEXT("ModeName", "TestEditorMode"),
		FSlateIcon(),
		true);
}


UTestEditorModeEditorMode::~UTestEditorModeEditorMode()
{
}


void UTestEditorModeEditorMode::ActorSelectionChangeNotify()
{
}

void UTestEditorModeEditorMode::Enter()
{
	UEdMode::Enter();

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// AddYourTool Step 2 - register the ToolBuilders for your Tools here.
	// The string name you pass to the ToolManager is used to select/activate your ToolBuilder later.
	//////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////// 
	const FTestEditorModeEditorModeCommands& SampleToolCommands = FTestEditorModeEditorModeCommands::Get();

	RegisterTool(SampleToolCommands.SimpleTool, SimpleToolName, NewObject<UTestEditorModeSimpleToolBuilder>(this));
	RegisterTool(SampleToolCommands.InteractiveTool, InteractiveToolName, NewObject<UTestEditorModeInteractiveToolBuilder>(this));

	// active tool type is not relevant here, we just set to default
	GetToolManager()->SelectActiveToolType(EToolSide::Left, SimpleToolName);
}

void UTestEditorModeEditorMode::CreateToolkit()
{
	Toolkit = MakeShareable(new FTestEditorModeEditorModeToolkit);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> UTestEditorModeEditorMode::GetModeCommands() const
{
	return FTestEditorModeEditorModeCommands::Get().GetCommands();
}

#undef LOCTEXT_NAMESPACE
