// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IImageWrapperModule.h"

#include "VLTET_MaterialHandler_BPLibrary.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EJoyImageFormats : uint8
{
	JPG		UMETA(DisplayName = "JPG"),
	PNG		UMETA(DisplayName = "PNG"),
	BMP		UMETA(DisplayName = "BMP"),
	ICO		UMETA(DisplayName = "ICO"),
	EXR		UMETA(DisplayName = "EXR"),
	ICNS	UMETA(DisplayName = "ICNS")
};



UENUM(BlueprintType)
enum class ETextureType : uint8
{
	DIFFUSE		UMETA(DisplayName = "DIFFUSE"),
	ROUGHNESS		UMETA(DisplayName = "ROUGHNESS"),
	METALLIC		UMETA(DisplayName = "METALLIC"),
	NORMAL		UMETA(DisplayName = "NORMAL"),
	OPACITY		UMETA(DisplayName = "OPACITY"),
	EMISSIVE	UMETA(DisplayName = "EMISSIVE"),
	AO	UMETA(DisplayName = "AO"),
	DISPLACEMENT	UMETA(DisplayName = "DISPLACEMENT")
};




UCLASS()
class VLTEDITORTOOL_API UVLTET_MaterialHandler_BPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()



		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Texture Type From Path", Keywords = "VLTEditorTool Get Texture Type From Path Image Texture Source Path IO bat bash"), Category = "VLT - Material & Texture IO")
		static ETextureType GetTextureTypeFromPath(FString Source);
	
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Convert Texture Path Type To Another Path Type", Keywords = "VLTEditorTool Get onvert Texture Path Type To Another Path Type Source Path IO bat bash"), Category = "VLT - Material & Texture IO")
		static FString ConvertTexturePathTypeToAnotherPathType(FString Source, ETextureType TargetType);
	
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Normal From Image", Keywords = "VLTEditorTool Normal From Image Texture Source Path IO bat bash"), Category = "VLT - Material & Texture IO")
		static void NormalFromSelectedAssetTexture();

	
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Import Asset From Path", Keywords = "VLTEditorTool Get Texture Source Path IO bat bash"), Category = "VLT - File IO")
		static void ImportAssetFromPath (FString Source, FString RelativeOutputName, FString AssetBaseName, EJoyImageFormats ImageFormat);
	
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Load Texture From Path", Keywords = "VLTEditorTool Load Texture From Path"), Category = "VLT - Material & Texture IO")
		static UTexture2D* LoadTextureFromPath(const FString& FilePath, const FString& FileName, EJoyImageFormats ImageFormat);
	
		static EImageFormat GetJoyImageFormat(EJoyImageFormats JoyFormat);
	
	
		static FString GetJoyImageExtension(EJoyImageFormats JoyFormat);
	
};
