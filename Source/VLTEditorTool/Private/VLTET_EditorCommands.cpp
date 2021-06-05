// Fill out your copyright notice in the Description page of Project Settings.


#include "VLTET_EditorCommands.h"


#define LOCTEXT_NAMESPACE "VLTET_EditorCommands"

void VLTET_EditorCommands::RegisterCommands()
{
	UI_COMMAND(TestCommand, "TestCommand", "This is test command", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE