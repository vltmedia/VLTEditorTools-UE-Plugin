// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "SlateBasics.h"
#include "EditorStyleSet.h"

#include "CoreMinimal.h"

/**
 * 
 */


class VLTEDITORTOOL_API VLTET_EditorCommands : public TCommands<VLTET_EditorCommands>
{
public:

	VLTET_EditorCommands()
		: TCommands<VLTET_EditorCommands>
		(
			TEXT("TutorialPluginEditor"),
			NSLOCTEXT("Contexts", "TutorialPluginEditor", "TutorialPluginEditor Plugin"),
			NAME_None,
			FEditorStyle::GetStyleSetName()
			) {}

	virtual void RegisterCommands() override;
	// UI Command functions
	//void TestCommand();
	//void MapCommands();

protected: 
	//TSharedPtr<FUICommandList> CommandList;
public:

	TSharedPtr<FUICommandInfo> TestCommand;
};