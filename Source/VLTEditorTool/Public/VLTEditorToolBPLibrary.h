// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "HAL/PlatformFilemanager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "VLTEditorToolBPLibrary.generated.h"


/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class UVLTEditorToolBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Copy Directory to Directory", Keywords = "VLTEditorTool File IO Copy Directory"), Category = "VLT - File IO")
	static void CopyDirectoryToDirectory(FString Source, FString Target, bool Overwrite = false);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Copy Relative File to Relative File", Keywords = "VLTEditorTool File IO Copy Directory"), Category = "VLT - File IO")
	static void CopyFileToFile(FString Source, FString Target);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Relative Path To Full Path", Keywords = "VLTEditorTool File IO Copy Directory"), Category = "VLT - File IO")
	static FString RelativePathToFullPath(FString Source);

	UFUNCTION(BlueprintCallable, Category = "VLT - Editor Helper")
		static TArray<FString>   GetSelectedFolderInContentBrowser();

	UFUNCTION(BlueprintCallable, Category = "VLT - Editor Helper")
		static TArray<FAssetData>   GetSelectedAssetsInContentBrowser();

	UFUNCTION(BlueprintCallable, Category = "VLT - Editor Helper")
		static TArray<AActor*>  GetSelectedActorsInScene();

	UFUNCTION(BlueprintCallable, Category = "VLT - Editor Helper")
		static AActor* GetSelectedActorInScene();
	UFUNCTION(BlueprintCallable, Category = "VLT - Editor Helper")
		static AActor* GetSelectedActorInSceneByIndex(int32 index);



	//Editor UI
	UFUNCTION(BlueprintCallable, Category = "VLT - Editor GUI Helper")
		static void ShowEditorAlert(FString message = "Something Happened", float FadeInDuration = 0.1f, float FadeoutDuration = 0.5f, float ExpireDuration = 1.5f);

	UFUNCTION(BlueprintCallable, Category = "VLT - Editor Helper")
		static  FSlateBrush FSlateImageFromAssetPath(FString AssetPath, int64 width, int64 height);


	UFUNCTION(BlueprintCallable, Category = "VLT - Editor Helper")
		static  FString GetGameContentPath();



	UFUNCTION(BlueprintCallable, Category = "VLT - Editor Helper")
		static  void SelectActorInEditor();



};
