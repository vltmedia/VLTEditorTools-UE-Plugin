// Fill out your copyright notice in the Description page of Project Settings.

#include "HAL/PlatformFilemanager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "AssetRegistryModule.h"
#include "DDSLoader.h"
#include "VLTET_MaterialHandler_BPLibrary.h"
#include "VLTEditorToolBPLibrary.h"
#include "Misc/Paths.h"
#include "IImageWrapperModule.h"
#include <Runtime\Core\Public\Misc\FileHelper.h>
#include <Runtime\ImageWrapper\Public\IImageWrapper.h>

void UVLTET_MaterialHandler_BPLibrary::NormalFromSelectedAssetTexture()
{

	TArray<FAssetData> assets = UVLTEditorToolBPLibrary::GetSelectedAssetsInContentBrowser();
	auto focusasset = assets[0];
	auto currentasset = focusasset.GetAsset();
	FString AssetFolder = focusasset.PackagePath.ToString().Replace(TEXT("/Game/"), *UVLTEditorToolBPLibrary::GetGameContentPath());

	UTexture2D* currenttexture = Cast<UTexture2D>(currentasset); 
	FString texturesourcepath =  UVLTEditorToolBPLibrary::GetTextureSourcePath(currenttexture);
	UE_LOG(LogTemp, Warning, TEXT("texturesourcepath : %s"), *texturesourcepath);

	FString Basenamee = FPaths::GetCleanFilename(texturesourcepath);



	FString outputfolder = UVLTET_MaterialHandler_BPLibrary::ConvertTexturePathTypeToAnotherPathType(AssetFolder +'/'+ Basenamee, ETextureType::NORMAL);
	FString normalmaparguments = AssetFolder +"/"+ Basenamee +" "+ outputfolder;
	FString normalmapexe = FPaths::ProjectPluginsDir() + "VLTEditorTool/Content/Resources/normalmap.exe";
	UE_LOG(LogTemp, Warning, TEXT("Args : %s"), *normalmaparguments);

	UVLTEditorToolBPLibrary::CreateProcessWithArguments(normalmapexe, normalmaparguments,false, false, false, 100, FPaths::ProjectPluginsDir());
	//UE_LOG(LogTemp, Warning, TEXT("Texture Source Path : %s"), *currentasset);
	UE_LOG(LogTemp, Warning, TEXT("Asset Source Path : %s"), *AssetFolder);


}

ETextureType UVLTET_MaterialHandler_BPLibrary::GetTextureTypeFromPath(FString Source) {


	const FString DiffuseArray[] = { TEXT("Diffuse"), TEXT("_dif") , TEXT("BaseColor") , TEXT("basecolor") , TEXT("diffuse") };
	const FString RoughnessArray[] = { TEXT("Rough") , TEXT("Roughness") };
	const FString NormalArray[] = { TEXT("Normal") , TEXT("_n"), TEXT("norm") };
	const FString MetallicArray[] = { TEXT("Metallic") , TEXT("Metalness"), TEXT("Metal") };
	const FString EmissiveArray[] = { TEXT("Emissive") , TEXT("Emission"), TEXT("Emit") };
	const FString AmbientOcclusionArray[] = { TEXT("AmbientOcclusion") , TEXT("_AO"), TEXT("Ambient"), TEXT("Occlusion"), TEXT("Oclusion") };
	const FString DisplacementArray[] = { TEXT("Displacement") , TEXT("_height"), TEXT("displacement"), TEXT("displace"), TEXT("PixelOffset") };
	const FString OpacityArray[] = { TEXT("opacity") , TEXT("transparancy"), TEXT("alpha") };

	for (FString CompareString : DiffuseArray) {
		if (Source.Contains(CompareString)) {

			return ETextureType::DIFFUSE;
		}
	}
	
	for (FString CompareString : RoughnessArray) {
		if (Source.Contains(CompareString)) {

			return ETextureType::ROUGHNESS;
		}
	}
	
	for (FString CompareString : NormalArray) {
		if (Source.Contains(CompareString)) {

			return ETextureType::NORMAL;
		}
	}
	
	for (FString CompareString : MetallicArray) {
		if (Source.Contains(CompareString)) {

			return ETextureType::METALLIC;
		}
	}
	
	for (FString CompareString : EmissiveArray) {
		if (Source.Contains(CompareString)) {

			return ETextureType::EMISSIVE;
		}
	}
	
	for (FString CompareString : AmbientOcclusionArray) {
		if (Source.Contains(CompareString)) {

			return ETextureType::AO;
		}
	}
	
	for (FString CompareString : DisplacementArray) {
		if (Source.Contains(CompareString)) {

			return ETextureType::DISPLACEMENT;
		}
	}
	
	for (FString CompareString : OpacityArray) {
		if (Source.Contains(CompareString)) {

			return ETextureType::OPACITY;
		}
	}

	return ETextureType::DIFFUSE;

}

FString UVLTET_MaterialHandler_BPLibrary::ConvertTexturePathTypeToAnotherPathType(FString Source, ETextureType TargetType)
{
	//ETextureType CurrentType = UVLTET_MaterialHandler_BPLibrary::GetTextureTypeFromPath(Source);
	FString SourceTypeText = "_Diffuse";
	FString ReplaceTypeText = "Diffuse";
	if (TargetType == ETextureType::AO) { ReplaceTypeText = "AO"; }
	if (TargetType == ETextureType::DISPLACEMENT) { ReplaceTypeText = "Displacement"; }
	if (TargetType == ETextureType::EMISSIVE) { ReplaceTypeText = "Emissive"; }
	if (TargetType == ETextureType::METALLIC) { ReplaceTypeText = "Metallic"; }
	if (TargetType == ETextureType::NORMAL) { ReplaceTypeText = "Normal"; }
	if (TargetType == ETextureType::OPACITY) { ReplaceTypeText = "Opacity"; }
	if (TargetType == ETextureType::ROUGHNESS) { ReplaceTypeText = "Roughness"; }
	FString SourcePath = Source;

	const FString DiffuseArray[] = { TEXT("Diffuse"), TEXT("_dif") , TEXT("BaseColor") , TEXT("basecolor") , TEXT("diffuse") };
	const FString RoughnessArray[] = { TEXT("Rough") , TEXT("Roughness") };
	const FString NormalArray[] = { TEXT("Normal") , TEXT("_n"), TEXT("norm") };
	const FString MetallicArray[] = { TEXT("Metallic") , TEXT("Metalness"), TEXT("Metal") };
	const FString EmissiveArray[] = { TEXT("Emissive") , TEXT("Emission"), TEXT("Emit") };
	const FString AmbientOcclusionArray[] = { TEXT("AmbientOcclusion") , TEXT("_AO"), TEXT("Ambient"), TEXT("Occlusion"), TEXT("Oclusion") };
	const FString DisplacementArray[] = { TEXT("Displacement") , TEXT("_height"), TEXT("displacement"), TEXT("displace"), TEXT("PixelOffset") };
	const FString OpacityArray[] = { TEXT("opacity") , TEXT("transparancy"), TEXT("alpha") };

	for (FString CompareString : DiffuseArray) {
		if (Source.Contains(CompareString)) {
			SourceTypeText = CompareString;
		}
	}

	for (FString CompareString : RoughnessArray) {
		if (Source.Contains(CompareString)) {
			SourceTypeText = CompareString;

		}
	}

	for (FString CompareString : NormalArray) {
		if (Source.Contains(CompareString)) {
			SourceTypeText = CompareString;

		}
	}

	for (FString CompareString : MetallicArray) {
		if (Source.Contains(CompareString)) {

			SourceTypeText = CompareString;

		}
	}

	for (FString CompareString : EmissiveArray) {
		if (Source.Contains(CompareString)) {

			SourceTypeText = CompareString;

		}
	}

	for (FString CompareString : AmbientOcclusionArray) {
		if (Source.Contains(CompareString)) {

			SourceTypeText = CompareString;

		}
	}

	for (FString CompareString : DisplacementArray) {
		if (Source.Contains(CompareString)) {

			SourceTypeText = CompareString;

		}
	}

	for (FString CompareString : OpacityArray) {
		if (Source.Contains(CompareString)) {

			SourceTypeText = CompareString;

		}
	}

	return Source.Replace(*SourceTypeText, *ReplaceTypeText);



}


void UVLTET_MaterialHandler_BPLibrary::ImportAssetFromPath(FString Source, FString RelativeOutputName, FString AssetBaseName, EJoyImageFormats ImageFormat)
{
    UTexture2D* tmpTexture = LoadTextureFromPath(Source, AssetBaseName, ImageFormat);
    FString PackageName = RelativeOutputName;
    UPackage* Package = CreatePackage(NULL, *PackageName);


	if (RelativeOutputName.Contains("/Game/")) {

		UE_LOG(LogTemp, Warning, TEXT("Updating Game Relative Folder %s"), *RelativeOutputName);
		FString updatee = RelativeOutputName.Replace(TEXT("/Game/"), *UVLTEditorToolBPLibrary::GetGameContentPath());
		RelativeOutputName = updatee;
		UE_LOG(LogTemp, Warning, TEXT("Updated Game Relative Folder %s"), *RelativeOutputName);
	}
	


	IPlatformFile& F = FPlatformFileManager::Get().GetPlatformFile();
	F.CopyFile(*RelativeOutputName, *Source, EPlatformFileRead::AllowWrite);

    //UTexture2D* NewAsset = NewObject< UTexture2D>(Package, FName(AssetBaseName), EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, tmpTexture, true);

    //if (NewAsset != NULL)
    //{
    //    // Fill in the assets data here
    //}

    //NewAsset->AddToRoot();
    //NewAsset->UpdateResource();
    //FAssetRegistryModule::AssetCreated(NewAsset);
    //NewAsset->MarkPackageDirty();

    UE_LOG(LogTemp, Warning, TEXT("source file path is %s"), *Source);
}

UTexture2D* UVLTET_MaterialHandler_BPLibrary::LoadTextureFromPath(const FString& FilePath,const FString& FileName, EJoyImageFormats ImageFormat)
{
   /* if (Path.IsEmpty()) return NULL;

    return Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *AssetName, *Path,  EObjectFlags::RF_Public | EObjectFlags::RF_Standalone));*/

	//IsValid = false;
	UTexture2D* LoadedT2D = NULL;

	

	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	IImageWrapperPtr ImageWrapper = ImageWrapperModule.CreateImageWrapper(GetJoyImageFormat(ImageFormat));

	//Load From File
	FString FullFilePath = FilePath;
	TArray<uint8> RawFileData;
	if (!FFileHelper::LoadFileToArray(RawFileData, *FullFilePath)) return NULL;

	//Create T2D!
	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
	{
		const TArray<uint8>* UncompressedBGRA = NULL;
		 TArray<uint8> textureData;
		 if(ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, textureData)){
			//if (ImageWrapper.Get)
		/*if (ImageWrapper->get(ERGBFormat::BGRA, 8, UncompressedBGRA, textureData)
		if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
		{*/
			LoadedT2D = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);

			//Valid?
			if (!LoadedT2D) return NULL;
			//~~~~~~~~~~~~~~

			////Out!
			//Width = ImageWrapper->GetWidth();
			//Height = ImageWrapper->GetHeight();

			//Copy!
			void* TextureData = LoadedT2D->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			FMemory::Memcpy(TextureData, textureData.GetData(), textureData.Num());
			LoadedT2D->PlatformData->Mips[0].BulkData.Unlock();

			//Update!
			LoadedT2D->UpdateResource();
		}
	}

	// Success!
	return LoadedT2D;

}

EImageFormat UVLTET_MaterialHandler_BPLibrary::GetJoyImageFormat(EJoyImageFormats JoyFormat)
{
	switch (JoyFormat) {
	case EJoyImageFormats::JPG: return EImageFormat::JPEG;
	case EJoyImageFormats::PNG: return EImageFormat::PNG;
	case EJoyImageFormats::BMP: return EImageFormat::BMP;
	case EJoyImageFormats::ICO: return EImageFormat::ICO;
	case EJoyImageFormats::EXR: return EImageFormat::EXR;
	case EJoyImageFormats::ICNS: return EImageFormat::ICNS;
	}

	return EImageFormat::JPEG;
}

FString UVLTET_MaterialHandler_BPLibrary::GetJoyImageExtension(EJoyImageFormats JoyFormat)
{
	switch (JoyFormat) {
	case EJoyImageFormats::JPG: return ".jpg";
	case EJoyImageFormats::PNG: return ".png";
	case EJoyImageFormats::BMP: return ".bmp";
	case EJoyImageFormats::ICO: return ".ico";
	case EJoyImageFormats::EXR: return ".exr";
	case EJoyImageFormats::ICNS: return ".icns";
	}
	return ".png";
}