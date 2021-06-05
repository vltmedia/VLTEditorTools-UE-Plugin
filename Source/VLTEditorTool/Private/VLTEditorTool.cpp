// Copyright Epic Games, Inc. All Rights Reserved.

#include "VLTEditorTool.h"
#include "VLTEditorToolBPLibrary.h"

#include "VLTET_EditorCommands.h"
#include "LevelEditor.h"
#include "UObject/ConstructorHelpers.h"


#define LOCTEXT_NAMESPACE "FVLTEditorToolModule"
TSharedRef<FWorkspaceItem> FVLTEditorToolModule::MenuRoot = FWorkspaceItem::NewGroup(FText::FromString("Menu Root"));


void FVLTEditorToolModule::AddMenuExtension(const FMenuExtensionDelegate& extensionDelegate, FName extensionHook, const TSharedPtr<FUICommandList>& CommandList, EExtensionHook::Position position)
{
	MenuExtender->AddMenuExtension(extensionHook, position, CommandList, extensionDelegate);
}

void FVLTEditorToolModule::MakePulldownMenu(FMenuBarBuilder& menuBuilder)
{
	menuBuilder.AddPullDownMenu(
		FText::FromString("Example"),
		FText::FromString("Open the Example menu"),
		FNewMenuDelegate::CreateRaw(this, &FVLTEditorToolModule::FillPulldownMenu),
		"Example",
		FName(TEXT("ExampleMenu"))
	);
}

void FVLTEditorToolModule::FillPulldownMenu(FMenuBuilder& menuBuilder)
{
	// just a frame for tools to fill in
	menuBuilder.BeginSection("ExampleSection", FText::FromString("Section 1"));
	menuBuilder.AddMenuSeparator(FName("Section_1"));
	menuBuilder.EndSection();

	menuBuilder.BeginSection("ExampleSection", FText::FromString("Section 2"));
	menuBuilder.AddMenuSeparator(FName("Section_2"));
	menuBuilder.EndSection();
}



void FVLTEditorToolModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	VLTET_EditorCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);
	PluginCommands->MapAction(
		VLTET_EditorCommands::Get().TestCommand,
		FExecuteAction::CreateRaw(this, &FVLTEditorToolModule::TestAction)
	);

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	{       
		MenuExtender = MakeShareable(new FExtender);

		TSharedPtr<FExtender> IconToolbarExtender = MakeShareable(new FExtender);
		IconToolbarExtender->AddToolBarExtension("Content",
			EExtensionHook::Before,
			PluginCommands,
			FToolBarExtensionDelegate::CreateRaw(this, &FVLTEditorToolModule::AddToolbarButton));
		MenuExtender->AddMenuBarExtension("Window", EExtensionHook::After, NULL, FMenuBarExtensionDelegate::CreateRaw(this, &FVLTEditorToolModule::MakePulldownMenu));
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(IconToolbarExtender);
		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}




}

void FVLTEditorToolModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	VLTET_EditorCommands::Unregister();

}


void FVLTEditorToolModule::AddToolbarButton(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(VLTET_EditorCommands::Get().TestCommand);
}

void FVLTEditorToolModule::TestAction()
{
	UE_LOG(LogTemp, Warning, TEXT("It Works!!!"));
	UPROPERTY()
	//TSoftClassPtr<UBlueprint> widgetfinder = TSoftClassPtr<UBlueprint>(FSoftObjectPath(TEXT("/VLTEditorTool/EditorTools/EUI/VLTEditorTool/EUI_CopyDirectoryToContent.EUI_CopyDirectoryToContent")));
		UObject* Obj = LoadObject<UObject>(NULL, TEXT("/VLTEditorTool/EditorTools/EUI/VLTEditorTool/EUI_CopyDirectoryToContent.EUI_CopyDirectoryToContent"), NULL, LOAD_None, NULL);
	UBlueprint* bpp = Cast<UBlueprint>(Obj);

	if (bpp->IsValidLowLevel()) {

	
		if (bpp->GeneratedClass->IsChildOf(UEditorUtilityWidget::StaticClass()))
		{
		
			UEditorUtilityWidget* CDO = Cast<UEditorUtilityWidget>(bpp->GeneratedClass->GetDefaultObject());
			
			if (CDO->ShouldAutoRunDefaultAction())
			{
				// This is an instant-run blueprint, just execute it
				UEditorUtilityWidget* Instance = NewObject<UEditorUtilityWidget>(GetTransientPackage(), bpp->GeneratedClass);
				Instance->ExecuteDefaultAction();
			}
			else
			{
				FName RegistrationName = FName(*(bpp->GetPathName() + TEXT("_ActiveTab")));
				FText DisplayName = FText::FromString(bpp->GetName());
				FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
				//FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<UEditorUtilityWidget>(TEXT("LevelEditor"));
				LevelEditorModule.GetLevelEditorTabManager()->InvokeTab(RegistrationName);
				

		
			}


		}
	}
	else {

		FString alertt = "Failed!";
		UVLTEditorToolBPLibrary::ShowEditorAlert(alertt, 0.1f, 0.5f, 5.0f);
	}
	/*UE_LOG(LogTemp, Warning, TEXT("Asset Name : %s"), bpp->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Long Package Name : %s"), bpp->GetPathName());


	UE_LOG(LogTemp, Warning, TEXT("IsChildOf(UEditorUtilityWidget::StaticClass() : %s"), bpp->GeneratedClass->IsChildOf(UEditorUtilityWidget::StaticClass()));*/

}

void FVLTEditorToolModule::SpawnEditorUtilityWidget(const TCHAR* assetpath)
{

	UObject* Obj = LoadObject<UObject>(NULL, assetpath, NULL, LOAD_None, NULL);
	UBlueprint* bpp = Cast<UBlueprint>(Obj);

	if (bpp->IsValidLowLevel()) {


		if (bpp->GeneratedClass->IsChildOf(UEditorUtilityWidget::StaticClass()))
		{

			UEditorUtilityWidget* CDO = Cast<UEditorUtilityWidget>(bpp->GeneratedClass->GetDefaultObject());

			if (CDO->ShouldAutoRunDefaultAction())
			{
				// This is an instant-run blueprint, just execute it
				UEditorUtilityWidget* Instance = NewObject<UEditorUtilityWidget>(GetTransientPackage(), bpp->GeneratedClass);
				Instance->ExecuteDefaultAction();
			}
			else
			{
				FName RegistrationName = FName(*(bpp->GetPathName() + TEXT("_ActiveTab")));
				FText DisplayName = FText::FromString(bpp->GetName());
				FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
				//FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<UEditorUtilityWidget>(TEXT("LevelEditor"));
				LevelEditorModule.GetLevelEditorTabManager()->InvokeTab(RegistrationName);

			}
		}
	}
	else {

		FString alertt = "(ERROR 10039) Failed spawning Editor UtilityWidget!";
		UVLTEditorToolBPLibrary::ShowEditorAlert(alertt, 0.1f, 0.5f, 5.0f);
	}

}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FVLTEditorToolModule, VLTEditorTool)