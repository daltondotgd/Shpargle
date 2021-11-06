// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShpargleStyle.h"
#include "ShpargleEditor.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FShpargleStyle::StyleInstance = nullptr;

void FShpargleStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FShpargleStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FShpargleStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("ShpargleStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef<FSlateStyleSet> FShpargleStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("ShpargleStyle"));
	Style->SetContentRoot(FPaths::EngineDir() / TEXT("Content/Slate/Starship/Common"));

	Style->Set("Shpargle.CreateBlueprintAction", new IMAGE_BRUSH_SVG(TEXT("Blueprint"), Icon20x20));
	Style->Set("Shpargle.RestartEditorAction", new IMAGE_BRUSH_SVG(TEXT("Refresh"), Icon20x20));
	return Style;
}

void FShpargleStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FShpargleStyle::Get()
{
	return *StyleInstance;
}
