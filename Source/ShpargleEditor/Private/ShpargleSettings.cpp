// Fill out your copyright notice in the Description page of Project Settings.


#include "ShpargleSettings.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "ISettingsEditorModule.h"
#include "ShpargleEditor.h"

#define LOCTEXT_NAMESPACE "ShpargleSettings"

void UShpargleSettings::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.Property)
	{
		bool bPromptRestartRequired = false;
		FName PropertyName = PropertyChangedEvent.Property->GetFName();

		if (PropertyName == GET_MEMBER_NAME_CHECKED(UShpargleSettings, bEnableExperimentalTools)
			|| PropertyName == GET_MEMBER_NAME_CHECKED(UShpargleSettings, bEnableTestTools))
		{
			//FShpargleEditorModule& ShpargleEditor = FModuleManager::GetModuleChecked<FShpargleEditorModule>("ShpargleEditor");
			//ShpargleEditor.RegisterMenus();
			bPromptRestartRequired = true;
		}

		// ...

		if (bPromptRestartRequired)
		{
			ISettingsEditorModule& SettingsEditorModule = FModuleManager::GetModuleChecked<ISettingsEditorModule>("SettingsEditor");
			SettingsEditorModule.OnApplicationRestartRequired();
		}
	}
}

#undef LOCTEXT_NAMESPACE