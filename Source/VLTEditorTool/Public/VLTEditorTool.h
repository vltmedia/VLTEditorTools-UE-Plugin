// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Editor/Blutility/Classes/EditorUtilityWidget.h"

#include "Modules/ModuleManager.h"
class FToolBarBuilder;

class FVLTEditorToolModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	TSharedPtr<class FUICommandList> PluginCommands;


	void AddToolbarButton(FToolBarBuilder& Builder);
	void TestAction();
	void SpawnEditorUtilityWidget(const TCHAR* assetpath);
	void AddMenuExtension(const FMenuExtensionDelegate& extensionDelegate, FName extensionHook, const TSharedPtr<FUICommandList>& CommandList = NULL, EExtensionHook::Position position = EExtensionHook::Before);
	TSharedRef<FWorkspaceItem> GetMenuRoot() { return MenuRoot; };
	static void SpawnCopyDirectoryTogameDirWindow();
	//static TSharedRef<SDockTab> SpawnEditorUITab(const FSpawnTabArgs& SpawnTabArgst, UWidgetBlueprint* Blueprint);
	//static TSharedRef<SDockTab> FVLTEditorToolModule::SpawnEditorUITab(const FSpawnTabArgs& SpawnTabArgst, UWidgetBlueprint* Blueprint) {
	//	TSharedRef< SDockTab> SpawnedTab = SNew(SDockTab);
	//	TSubclassOf<UUserWidget> WidgetClass = Blueprint->GeneratedClass;
	//	UWorld* World = GEditor->GetEditorWorldContext().World();
	//	check(World);
	//	UEditorUtilityWidget* CreatedUMGWidget = CreateWidget(World, WidgetClass);
	//	if (CreatedUMGWidget)
	//	{
	//		TSharedRef<SWidget> CreatedSlateWidget = CreatedUMGWidget->TakeWidget();
	//		SpawnedTab->SetContent(CreatedSlateWidget);
	//	}

	//	return SpawnedTab;
	//}
	//void OpenWidgetBlueprint(UWidgetBlueprint* Blueprint);



protected:
	TSharedPtr<FExtensibilityManager> LevelEditorMenuExtensibilityManager;
	TSharedPtr<FExtender> MenuExtender;
	TSharedPtr<FExtender> LevelEditorTabManager;

	static TSharedRef<FWorkspaceItem> MenuRoot;
	static TSharedRef<FWorkspaceItem> NewDockTab;

	void MakePulldownMenu(FMenuBarBuilder& menuBuilder);
	void FillPulldownMenu(FMenuBuilder& menuBuilder);
};
