// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IImageWrapperModule.h"
#include "Math/Color.h"
#include "ImageUtils.h"

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
	DISPLACEMENT	UMETA(DisplayName = "DISPLACEMENT"),
	ORM	UMETA(DisplayName = "ORM"),
	MATERIAL	UMETA(DisplayName = "MATERIAL")
};



UENUM(BlueprintType)
enum class ETextureChannel : uint8
{
	R		UMETA(DisplayName = "R"),
	G		UMETA(DisplayName = "G"),
	B		UMETA(DisplayName = "B"),
	A		UMETA(DisplayName = "A"),
	AVERAGE		UMETA(DisplayName = "AVERAGE"),
	WHITE		UMETA(DisplayName = "WHITE"),
	BLACK		UMETA(DisplayName = "BLACK"),
	ORIGINAL		UMETA(DisplayName = "ORIGINAL")

};

USTRUCT(BlueprintType)

struct FPPixels
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FColor> YPIXELS;
	


};

USTRUCT(BlueprintType)

struct FPPixelMatrix
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FPPixels> XPIXELS;
	


};


USTRUCT(BlueprintType)
struct FPTextureDimensions
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)

		TArray<int32> XPixels;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)

		TArray<int32> YPixels;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)

		TArray<int32> PIXELS;


};

USTRUCT(BlueprintType)
struct FPBRTexturePixels
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FColor> DIFFUSE_PIXELS;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FColor> ROUGHNESS_PIXELS;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FColor> METALLIC_PIXELS;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FColor> NORMAL_PIXELS;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FColor> OPACITY_PIXELS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FColor> EMISSIVE_PIXELS;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FColor> AO_PIXELS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FColor> DISPLACEMENT_PIXELS;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FColor> ORM_PIXELS;



};


USTRUCT(BlueprintType)
struct FPBRTextures
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* DIFFUSE_TEXTURE;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* ROUGHNESS_TEXTURE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* METALLIC_TEXTURE;


		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* NORMAL_TEXTURE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* OPACITY_TEXTURE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* EMISSIVE_TEXTURE;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* AO_TEXTURE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* DISPLACEMENT_TEXTURE;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* ORM_TEXTURE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FPBRTexturePixels PBRTexture_PIXELS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool UseORM;

	FPBRTextures(){
		DIFFUSE_TEXTURE = nullptr;
		ROUGHNESS_TEXTURE = nullptr;
		METALLIC_TEXTURE = nullptr;
		NORMAL_TEXTURE = nullptr;
		OPACITY_TEXTURE = nullptr;
		EMISSIVE_TEXTURE = nullptr;
		AO_TEXTURE = nullptr;
		DISPLACEMENT_TEXTURE = nullptr;
		ORM_TEXTURE = nullptr;
		UseORM = false;
	}


};



UCLASS()
class VLTEDITORTOOL_API UVLTET_MaterialHandler_BPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Texture Type From Path", Keywords = "VLTEditorTool Get Texture Type From Path Image Texture Source Path IO bat bash"), Category = "VLT - Material & Texture IO")
		static ETextureType GetTextureTypeFromPath(FString Source);
	
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Convert Texture Path Type To Another Path Type", Keywords = "VLTEditorTool Get onvert Texture Path Type To Another Path Type Source Path IO bat bash"), Category = "VLT - Material & Texture IO")
		static FString ConvertTexturePathTypeToAnotherPathType(FString Source, ETextureType TargetType);
	
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Normal From Image", Keywords = "VLTEditorTool Normal From Image Texture Source Path IO bat bash"), Category = "VLT - Material & Texture IO")
		static void NormalFromSelectedAssetTexture();
			
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Roughness From Image", Keywords = "VLTEditorTool Roughness From Image Texture Source Path IO bat bash"), Category = "VLT - Material & Texture IO")
		static void RoughnessFromSelectedAssetTexture();

	
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Import Asset From Path", Keywords = "VLTEditorTool Get Texture Source Path IO bat bash"), Category = "VLT - File IO")
		static void ImportAssetFromPath (FString Source, FString RelativeOutputName, FString AssetBaseName, EJoyImageFormats ImageFormat);
	
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Load Texture From Path", Keywords = "VLTEditorTool Load Texture From Path"), Category = "VLT - Material & Texture IO")
		static UTexture2D* LoadTextureFromPath(const FString& FilePath, const FString& FileName, EJoyImageFormats ImageFormat);
	
		static EImageFormat GetJoyImageFormat(EJoyImageFormats JoyFormat);
	
	
		static FString GetJoyImageExtension(EJoyImageFormats JoyFormat);

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Organize Textures Into PBR Texture Pack", Keywords = "VLTEditorTool Organize Textures Into PBR Texture Pack as a TArray"), Category = "VLT - Material & Texture IO")
			static FPBRTextures OrganizeTexturesIntoPBRTexturePack(TArray<UTexture2D*> Textures);
		
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Packed Texture ORM From Selected Textures", Keywords = "VLTEditorTool et a specific channel from a Texture2D as a TArray"), Category = "VLT - Material & Texture IO")
			static bool CreatePackedTextureORMFromSelectedTextures();


		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create PBR Material From Selected Textures", Keywords = "VLTEditorTool  PBR Material From Selected Textures TArray"), Category = "VLT - Material & Texture IO")
			static FPBRTextures CreatePBRMaterialFromSelectedTextures();

		// Pixel Stuff

	
		
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Channel From Texture As Color Array", Keywords = "VLTEditorTool et a specific channel from a Texture2D as a TArray"), Category = "VLT - Material & Texture IO")
			static TArray<FColor> GetChannelFromTexture(UTexture2D* Source, ETextureChannel TargetChannel);
					
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pixel Array To Pixel Matrix", Keywords = "VLTEditorTool Pixel Array To Pixel Matrix TArray"), Category = "VLT - Material & Texture IO")
			static FPPixelMatrix PixelArrayToPixelMatrix(TArray<FColor> Source, int32 sizeX, int32 sizeY);
								
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pixel Matrix To Pixel Array", Keywords = "VLTEditorTool Pixel Matrix To Pixel Array"), Category = "VLT - Material & Texture IO")
			static TArray<FColor> PixelMatrixToPixelArray(FPPixelMatrix Source, int32 sizeX, int32 sizeY);
			
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Single Color Pixel Array", Keywords = "VLTEditorTool Create Single Color Pixel Array as a TArray"), Category = "VLT - Material & Texture IO")
			static TArray<FColor> CreateSingleColorPixelArray(FColor TargetColor,int32 sizeX, int32 sizeY);
		
		
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Save Color Array As PNG", Keywords = "VLTEditorTool Save Bitmap As PNG TArray"), Category = "VLT - Material & Texture IO")
			static bool SaveColorArrayAsPNG(int32 sizeX, int32 sizeY, const TArray<FColor>& bitmapData, const FString& filePath);
						
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Check Pixel Array If Empty", Keywords = "VLTEditorTool Check Pixel Array If Empty TArray"), Category = "VLT - Material & Texture IO")
			static bool CheckPixelArrayIfEmpty(const TArray<FColor>& bitmapData);
								
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Check Empty Textures In Pack", Keywords = "VLTEditorTool Check Empty Textures In Pack TArray"), Category = "VLT - Material & Texture IO")
			static FPBRTextures CheckEmptyTexturesInPack(FPBRTextures PBRTextures);
													
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "PBR Texture Pack From Selected Assets", Keywords = "VLTEditorTool PBR Texture Pack From Selected Assets TArray"), Category = "VLT - Material & Texture IO")
			static FPBRTextures PBRTexturePackFromSelectedAssets();
												
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Check Empty Textures In Pack", Keywords = "VLTEditorTool Check Empty Textures In Pack TArray"), Category = "VLT - Material & Texture IO")
			static TArray<int32> GetTextureDimensionsFromPbrTexturePack(FPBRTextures PBRTextures);
				
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Packed Texture ORM From Textures", Keywords = "VLTEditorTool Create Packed Texture ORM From Textures"), Category = "VLT - Material & Texture IO")
			static bool CreatePackedTextureORMFromTextures(UTexture2D* OcclusionTexture, UTexture2D* RoughnessTexture, UTexture2D* MetallicTexture, const FString& filePath);
		
						
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Packed Texture ORM From Color Array", Keywords = "VLTEditorTool Create Packed Texture ORM From Textures"), Category = "VLT - Material & Texture IO")
			static bool CreatePackedTextureORMFromColorArray(const TArray<FColor>& OcclusionTexture, const TArray<FColor>& RoughnessTexture, const TArray<FColor>& MetallicTexture, int32 sizeX, int32 sizeY, const FString& filePath);
		
								
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Packed Texture ORM From Pbr Texture Pack", Keywords = "VLTEditorTool Create Packed Texture ORM From Textures"), Category = "VLT - Material & Texture IO")
			static bool CreatePackedTextureORMFromPBRTexturePack(FPBRTextures PbrTexturePack, const FString& filePath);
		

		//Get a specific channel from a Texture2D, then create a new Texture2D from that channel and return it as a ```UTexture2D```
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Channel From Texture To Texture", Keywords = "VLTEditorTool et a specific channel from a Texture2D as a TArray"), Category = "VLT - Material & Texture IO")
			static UTexture2D* ChannelFromTextureToTexture(UTexture2D* Source, ETextureChannel TargetChannel , const bool UseAlpha = false);


	
};
