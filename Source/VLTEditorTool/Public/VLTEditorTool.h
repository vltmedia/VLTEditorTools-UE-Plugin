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

protected:
	TSharedPtr<FExtensibilityManager> LevelEditorMenuExtensibilityManager;
	TSharedPtr<FExtender> MenuExtender;
	TSharedPtr<FExtender> LevelEditorTabManager;

	static TSharedRef<FWorkspaceItem> MenuRoot;
	static TSharedRef<FWorkspaceItem> NewDockTab;

	void MakePulldownMenu(FMenuBarBuilder& menuBuilder);
	void FillPulldownMenu(FMenuBuilder& menuBuilder);
};
