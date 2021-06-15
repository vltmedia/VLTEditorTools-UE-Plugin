// Fill out your copyright notice in the Description page of Project Settings.
#include "VLTET_MaterialHandler_BPLibrary.h"

#include "HAL/PlatformFilemanager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "AssetRegistryModule.h"
#include "DDSLoader.h"
#include "VLTEditorToolBPLibrary.h"
#include "Misc/Paths.h"
#include <exception>
#include "EditorFramework/AssetImportData.h"

#include "IImageWrapperModule.h"
#include <Runtime\Core\Public\Misc\FileHelper.h>
#include <Runtime\ImageWrapper\Public\IImageWrapper.h>
#include "EditorAssetLibrary.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceConstant.h"

void UVLTET_MaterialHandler_BPLibrary::NormalFromSelectedAssetTexture()
{

	TArray<FAssetData> assets = UVLTEditorToolBPLibrary::GetSelectedAssetsInContentBrowser();
	for (auto assett : assets) {
		auto focusasset = assett;
		auto currentasset = focusasset.GetAsset();
		FString AssetFolder = focusasset.PackagePath.ToString().Replace(TEXT("/Game/"), *UVLTEditorToolBPLibrary::GetGameContentPath());

		UTexture2D* currenttexture = Cast<UTexture2D>(currentasset);
		FString texturesourcepath = FPaths::ConvertRelativePathToFull(UVLTEditorToolBPLibrary::GetTextureSourcePath(currenttexture));
		UE_LOG(LogTemp, Warning, TEXT("texturesourcepath : %s"), *texturesourcepath);

		FString Basenamee = FPaths::GetCleanFilename(texturesourcepath);



		FString outputfolder = UVLTET_MaterialHandler_BPLibrary::ConvertTexturePathTypeToAnotherPathType(AssetFolder + '/' + Basenamee, ETextureType::NORMAL).Replace(TEXT(".jpg"), TEXT(".png"));
		//FString normalmaparguments = AssetFolder +"/"+ Basenamee +" "+ outputfolder;
		FString normalmaparguments = "\"" + FPaths::ConvertRelativePathToFull(UVLTEditorToolBPLibrary::GetTextureSourcePath(currenttexture)) + "\" \"" + outputfolder + "\"";

		FString normalmapexe = FPaths::ProjectPluginsDir() + "VLTEditorTool/Content/Resources/normalmap.exe";
		UE_LOG(LogTemp, Warning, TEXT("Args : %s"), *normalmaparguments);
		UE_LOG(LogTemp, Warning, TEXT("Command : \"%s\" %s"), *normalmapexe, *normalmaparguments);

		UVLTEditorToolBPLibrary::CreateProcessWithArguments(normalmapexe, normalmaparguments, false, false, false, 100, FPaths::ProjectPluginsDir());
		//UE_LOG(LogTemp, Warning, TEXT("Texture Source Path : %s"), *currentasset);
		UE_LOG(LogTemp, Warning, TEXT("Asset Source Path : %s"), *AssetFolder);
	}

}

void UVLTET_MaterialHandler_BPLibrary::RoughnessFromSelectedAssetTexture()
{

	TArray<FAssetData> assets = UVLTEditorToolBPLibrary::GetSelectedAssetsInContentBrowser();
	for (auto assett : assets) {
	auto focusasset = assett;
	auto currentasset = focusasset.GetAsset();
	FString AssetFolder = focusasset.PackagePath.ToString().Replace(TEXT("/Game/"), *UVLTEditorToolBPLibrary::GetGameContentPath());

	UTexture2D* currenttexture = Cast<UTexture2D>(currentasset); 
	FString texturesourcepath =  FPaths::ConvertRelativePathToFull(UVLTEditorToolBPLibrary::GetTextureSourcePath(currenttexture));
	UE_LOG(LogTemp, Warning, TEXT("texturesourcepath : %s"), *FPaths::ConvertRelativePathToFull(UVLTEditorToolBPLibrary::GetTextureSourcePath(currenttexture)));

	FString Basenamee = FPaths::GetCleanFilename(texturesourcepath);



	FString outputfolder = UVLTET_MaterialHandler_BPLibrary::ConvertTexturePathTypeToAnotherPathType(AssetFolder +'/'+ Basenamee, ETextureType::ROUGHNESS);
	FString normalmaparguments = "\""+ FPaths::ConvertRelativePathToFull(UVLTEditorToolBPLibrary::GetTextureSourcePath(currenttexture)) +"\" \""+ outputfolder+"\" Average"  ;
	FString normalmapexe = FPaths::ProjectPluginsDir() + "VLTEditorTool/Content/Resources/GenerateRoughness/GenerateRoughnessMap.exe";
	UE_LOG(LogTemp, Warning, TEXT("Args : %s"), *normalmaparguments);
	UE_LOG(LogTemp, Warning, TEXT("Command : \"%s\" %s"), *normalmapexe, *normalmaparguments);

	UVLTEditorToolBPLibrary::CreateProcessWithArguments(normalmapexe, normalmaparguments,false, false, false, 100, FPaths::ProjectPluginsDir());
	//UE_LOG(LogTemp, Warning, TEXT("Texture Source Path : %s"), *currentasset);
	UE_LOG(LogTemp, Warning, TEXT("Asset Source Path : %s"), *AssetFolder);
	}

}

ETextureType UVLTET_MaterialHandler_BPLibrary::GetTextureTypeFromPath(FString Source) {


	const FString DiffuseArray[] = { TEXT("Diffuse"), TEXT("_dif") , TEXT("BaseColor") , TEXT("basecolor"),TEXT("Base_Color") ,TEXT("Color") , TEXT("diffuse") };
	const FString RoughnessArray[] = { TEXT("Rough") , TEXT("Roughness") };
	const FString NormalArray[] = { TEXT("Normal") , TEXT("_n"), TEXT("norm") };
	const FString MetallicArray[] = { TEXT("Metallic") , TEXT("Metalness"), TEXT("Metal") };
	const FString EmissiveArray[] = { TEXT("Emissive") , TEXT("Emission"), TEXT("Emit") };
	const FString AmbientOcclusionArray[] = { TEXT("AmbientOcclusion") , TEXT("_AO"), TEXT("Ambient"), TEXT("Occlusion"), TEXT("Oclusion"), TEXT("Ambient_Occlusion") };
	const FString DisplacementArray[] = { TEXT("Displacement") , TEXT("_height"), TEXT("displacement"), TEXT("displace"), TEXT("PixelOffset") };
	const FString OpacityArray[] = { TEXT("opacity") , TEXT("transparancy"), TEXT("alpha") };
	const FString ORMArray[] = { TEXT("orm") , TEXT("ORM") , TEXT("_ORM"), TEXT("OcclusionRoughnessMetallic") };
	FString SourceCheck = Source.ToLower();
	UE_LOG(LogTemp, Warning, TEXT("Asset Source Path : %s"), *SourceCheck);

	for (FString CompareString : NormalArray) {
		if (SourceCheck.Contains(CompareString.ToLower())) {

			return ETextureType::NORMAL;
		}
	}
	for (FString CompareString : ORMArray) {
		if (SourceCheck.Contains(CompareString.ToLower())) {

			return ETextureType::ORM;
		}
	}
	for (FString CompareString : AmbientOcclusionArray) {
		UE_LOG(LogTemp, Warning, TEXT("CompareString ao : %s"), *CompareString);

		if (SourceCheck.Contains(CompareString.ToLower())) {

			return ETextureType::AO;
		}
	}

	for (FString CompareString : DiffuseArray) {
		if (SourceCheck.Contains(CompareString.ToLower())) {

			return ETextureType::DIFFUSE;
		}
	}
	for (FString CompareString : RoughnessArray) {
		if (SourceCheck.Contains(CompareString.ToLower())) {

			return ETextureType::ROUGHNESS;
		}
	}




	for (FString CompareString : EmissiveArray) {
		if (SourceCheck.Contains(CompareString.ToLower())) {

			return ETextureType::EMISSIVE;
		}
	}

	for (FString CompareString : DisplacementArray) {
		if (SourceCheck.Contains(CompareString.ToLower())) {

			return ETextureType::DISPLACEMENT;
		}
	}
	
	for (FString CompareString : OpacityArray) {
		if (SourceCheck.Contains(CompareString.ToLower())) {

			return ETextureType::OPACITY;
		}
	}

	for (FString CompareString : MetallicArray) {
		if (SourceCheck.Contains(CompareString.ToLower())) {

			return ETextureType::METALLIC;
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
		if (TargetType == ETextureType::ORM) { ReplaceTypeText = "ORM"; }
		FString SourcePath = Source;

		const FString DiffuseArray[] = { TEXT("Diffuse"), TEXT("_dif") , TEXT("BaseColor") ,TEXT("Color") , TEXT("basecolor") , TEXT("diffuse") ,TEXT("Base_Color") ,TEXT("Base Color") };
		const FString RoughnessArray[] = { TEXT("Rough") , TEXT("Roughness") };
		const FString NormalArray[] = { TEXT("Normal") , TEXT("_n"), TEXT("norm") };
		const FString MetallicArray[] = { TEXT("Metallic") , TEXT("Metalness") };
		const FString EmissiveArray[] = { TEXT("Emissive") , TEXT("Emission"), TEXT("Emit") };
		const FString AmbientOcclusionArray[] = { TEXT("AmbientOcclusion") , TEXT("_AO"), TEXT("Ambient"), TEXT("Occlusion"), TEXT("Oclusion") };
		const FString DisplacementArray[] = { TEXT("Displacement") , TEXT("_height"), TEXT("displacement"), TEXT("displace"), TEXT("PixelOffset") };
		const FString OpacityArray[] = { TEXT("opacity") , TEXT("transparancy"), TEXT("alpha") };
		const FString ORMArray[] = { TEXT("ORM") , TEXT("orm"), TEXT("packed") };

		for (FString CompareString : MetallicArray) {
			if (Source.Contains(CompareString)) {

				SourceTypeText = CompareString;

			}
		}
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

		for (FString CompareString : ORMArray) {
			if (Source.Contains(CompareString)) {

				SourceTypeText = CompareString;

			}
		}

		if (TargetType == ETextureType::MATERIAL) {
			FString CleanedBasename = Source.Replace(*SourceTypeText, TEXT(""));
			 ReplaceTypeText = "PBR_" + FPaths::GetBaseFilename(FPaths::GetPath(Source));
			 //ReplaceTypeText = "PBR_" + FPaths::GetBaseFilename(CleanedBasename).Replace(TEXT(" "), TEXT("_"));
			FString Directoryy = FPaths::GetPath(Source);
			FString outpath = Directoryy +"/" + ReplaceTypeText + '.' + ReplaceTypeText;
			UE_LOG(LogTemp, Warning, TEXT("Out Path:  %s"), *outpath);

			return outpath;
		}
		else {
			return Source.Replace(*SourceTypeText, *ReplaceTypeText);

		}
		
	

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

FPBRTextures UVLTET_MaterialHandler_BPLibrary::OrganizeTexturesIntoPBRTexturePack(TArray<UTexture2D*> Textures)
{
	FPBRTextures pbrOut;
	for (UTexture2D* text_ : Textures) {
		auto texturetype = UVLTET_MaterialHandler_BPLibrary::GetTextureTypeFromPath(text_->GetFullName());

		if (texturetype == ETextureType::DIFFUSE) { pbrOut.DIFFUSE_TEXTURE = text_; }
		if (texturetype == ETextureType::ROUGHNESS) { pbrOut.ROUGHNESS_TEXTURE = text_; }
		if (texturetype == ETextureType::METALLIC) { pbrOut.METALLIC_TEXTURE = text_; }
		if (texturetype == ETextureType::NORMAL) { pbrOut.NORMAL_TEXTURE = text_; }
		if (texturetype == ETextureType::OPACITY) { pbrOut.OPACITY_TEXTURE = text_; }
		if (texturetype == ETextureType::AO) { pbrOut.AO_TEXTURE = text_; }
		if (texturetype == ETextureType::DISPLACEMENT) { pbrOut.DISPLACEMENT_TEXTURE = text_; }
		if (texturetype == ETextureType::ORM) { pbrOut.ORM_TEXTURE = text_; }

	}

	return pbrOut;
}

bool UVLTET_MaterialHandler_BPLibrary::CreatePackedTextureORMFromSelectedTextures()
{
	FString AssetFolder = "";
	TArray<UTexture2D*> Textures;
	TArray<FAssetData> assets = UVLTEditorToolBPLibrary::GetSelectedAssetsInContentBrowser();
	for (auto assett : assets) {
		auto focusasset = assett;
		auto currentasset = focusasset.GetAsset();
		 AssetFolder = focusasset.PackagePath.ToString().Replace(TEXT("/Game/"), *UVLTEditorToolBPLibrary::GetGameContentPath());

		Textures.Add( Cast<UTexture2D>(currentasset));
	}


	FPBRTextures pbrTexturePack = UVLTET_MaterialHandler_BPLibrary::CheckEmptyTexturesInPack(UVLTET_MaterialHandler_BPLibrary::OrganizeTexturesIntoPBRTexturePack(Textures));


	UTexture2D* targetSourceTexture = pbrTexturePack.ROUGHNESS_TEXTURE;
	TArray<FColor> AOTex ;
	TArray<FColor> RoughnessTex ;
	TArray<FColor> MetallicTex;

	// Handle Setting Size
	int32 XSize = 10;
	int32 YSize = 10;
	if (pbrTexturePack.ROUGHNESS_TEXTURE != nullptr) { targetSourceTexture = pbrTexturePack.ROUGHNESS_TEXTURE; 	XSize = pbrTexturePack.ROUGHNESS_TEXTURE->GetSizeX();	YSize = pbrTexturePack.ROUGHNESS_TEXTURE->GetSizeY();	}
	else {
		if (pbrTexturePack.METALLIC_TEXTURE != nullptr) { targetSourceTexture = pbrTexturePack.METALLIC_TEXTURE; XSize = pbrTexturePack.METALLIC_TEXTURE->GetSizeX();	YSize = pbrTexturePack.METALLIC_TEXTURE->GetSizeY(); }
		else {
			if (pbrTexturePack.AO_TEXTURE != nullptr) { targetSourceTexture = pbrTexturePack.AO_TEXTURE; XSize = pbrTexturePack.AO_TEXTURE->GetSizeX();	YSize = pbrTexturePack.AO_TEXTURE->GetSizeY();}

		}

	}

	// Handle Output Filepath name.
	const FAssetImportInfo& AssetImportInfo = targetSourceTexture->AssetImportData->SourceData;
	FString SourceFilePath = "";

		 SourceFilePath = AssetImportInfo.SourceFiles[0].RelativeFilename;
		UE_LOG(LogTemp, Warning, TEXT("source file path is %s"), *SourceFilePath);



		FString texturesourcepath = FPaths::ConvertRelativePathToFull(UVLTEditorToolBPLibrary::GetTextureSourcePath(targetSourceTexture));
		

		FString Basenamee = FPaths::GetCleanFilename(texturesourcepath);



		FString outputpath = UVLTET_MaterialHandler_BPLibrary::ConvertTexturePathTypeToAnotherPathType(AssetFolder + '/' + Basenamee, ETextureType::ORM);

		UE_LOG(LogTemp, Warning, TEXT("texturesourcepath : %s"), *outputpath);

	FString filepath = UVLTET_MaterialHandler_BPLibrary::ConvertTexturePathTypeToAnotherPathType(SourceFilePath, ETextureType::ORM);

	if (UVLTET_MaterialHandler_BPLibrary::CreatePackedTextureORMFromPBRTexturePack(pbrTexturePack, outputpath)) {
		UVLTEditorToolBPLibrary::ShowEditorAlert("Successfully created ORM texture! " + outputpath);
		return true;
	}
	else {
		UVLTEditorToolBPLibrary::ShowEditorAlert("ERROR(10054) : Failed creating ORM texture! " + outputpath);

		return false;

	}
	return false;

}

FPBRTextures UVLTET_MaterialHandler_BPLibrary::CreatePBRMaterialFromSelectedTextures()
{

	FString BaseMaterial = "/VLTEditorTool/Materials/PBR/VLTPBR_Base_InstTemplate.VLTPBR_Base_InstTemplate";
	FString OpacityMaterialPath = "/VLTEditorTool/Materials/PBR/VLTPBR_OpacityBase_Inst.VLTPBR_OpacityBase_Inst";

	FString MaterialName = "/VLTEditorTool/Materials/PBR/VLTPBR_Base_InstTemplate.VLTPBR_Base_InstTemplate";
	FString AssetFolder = "/VLTEditorTool/Materials/PBR/VLTPBR_Base_InstTemplate.VLTPBR_Base_InstTemplate";
	FPBRTextures pbrTextures = UVLTET_MaterialHandler_BPLibrary::PBRTexturePackFromSelectedAssets();
	UTexture2D* targetSourceTexture = pbrTextures.DIFFUSE_TEXTURE;

	// Handle Material Output Filepath name.
	TArray<FAssetData> assets = UVLTEditorToolBPLibrary::GetSelectedAssetsInContentBrowser();
	for (auto assett : assets) {
		auto focusasset = assett;
		auto currentasset = focusasset.GetAsset();
		AssetFolder = focusasset.PackagePath.ToString().Replace(TEXT("/Game/"), *UVLTEditorToolBPLibrary::GetGameContentPath());

	}

	FString SourceFilePath = "";

	if (pbrTextures.DIFFUSE_TEXTURE != nullptr) {
		const FAssetImportInfo& AssetImportInfo = pbrTextures.DIFFUSE_TEXTURE->AssetImportData->SourceData;
		SourceFilePath = AssetImportInfo.SourceFiles[0].RelativeFilename;
		targetSourceTexture = pbrTextures.DIFFUSE_TEXTURE;
	}
	else {


		if (pbrTextures.ROUGHNESS_TEXTURE != nullptr) {
			const FAssetImportInfo& AssetImportInfo = pbrTextures.ROUGHNESS_TEXTURE->AssetImportData->SourceData;
			SourceFilePath = AssetImportInfo.SourceFiles[0].RelativeFilename;
			targetSourceTexture = pbrTextures.ROUGHNESS_TEXTURE;

		}
		else {
		}
		if (pbrTextures.METALLIC_TEXTURE != nullptr) {
			const FAssetImportInfo& AssetImportInfo = pbrTextures.METALLIC_TEXTURE->AssetImportData->SourceData;
			SourceFilePath = AssetImportInfo.SourceFiles[0].RelativeFilename;
			targetSourceTexture = pbrTextures.METALLIC_TEXTURE;

		}
		else {
		if (pbrTextures.NORMAL_TEXTURE != nullptr) {
			const FAssetImportInfo& AssetImportInfo = pbrTextures.NORMAL_TEXTURE->AssetImportData->SourceData;
			SourceFilePath = AssetImportInfo.SourceFiles[0].RelativeFilename;
			targetSourceTexture = pbrTextures.NORMAL_TEXTURE;

		}
		}
	}
	
	FString texturesourcepath = FPaths::ConvertRelativePathToFull(UVLTEditorToolBPLibrary::GetTextureSourcePath(targetSourceTexture));
	FString Basenamee = FPaths::GetCleanFilename(texturesourcepath);
	
	FString outputpath =  UVLTET_MaterialHandler_BPLibrary::ConvertTexturePathTypeToAnotherPathType(targetSourceTexture->GetPathName(), ETextureType::MATERIAL);
	UVLTEditorToolBPLibrary::ShowEditorAlert("Output texture! " + SourceFilePath);
	UE_LOG(LogTemp, Warning, TEXT("outputpath : %s"), *outputpath);


	// Create New MAterial
	UObject* NewMaterial = nullptr;
	if (pbrTextures.OPACITY_TEXTURE == nullptr) {
		NewMaterial = UEditorAssetLibrary::DuplicateAsset(BaseMaterial, outputpath);
	}
	else {

		NewMaterial = UEditorAssetLibrary::DuplicateAsset(OpacityMaterialPath, outputpath);
	}
	//UMaterialInstance* NewMaterialInstc = Cast<UMaterialInstance>(NewMaterial);
	UMaterialInstanceConstant* NewMaterialInst = Cast<UMaterialInstanceConstant>(NewMaterial);
	//FMaterialParameterInfo diff = FMaterialParameterInfo("DiffuseTexture");
	if (pbrTextures.DIFFUSE_TEXTURE != nullptr) { NewMaterialInst->SetTextureParameterValueEditorOnly(FMaterialParameterInfo("DiffuseTexture"), pbrTextures.DIFFUSE_TEXTURE); }
	//NewMaterialInstc->TextureParameterValues[0].ParameterInfo;
	//UE_LOG(LogTemp, Warning, TEXT("ParameterInfo 0 : %s"), *NewMaterialInst->GetMaterial()->parameter.ParameterInfo.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("ParameterInfo 0 val : %s"), *NewMaterialInst->TextureParameterValues[0].ParameterValue->GetName());
	

	if (pbrTextures.NORMAL_TEXTURE != nullptr) { NewMaterialInst->SetTextureParameterValueEditorOnly(FMaterialParameterInfo("NormalTexture"), pbrTextures.NORMAL_TEXTURE); }
	if (pbrTextures.DISPLACEMENT_TEXTURE != nullptr) { NewMaterialInst->SetTextureParameterValueEditorOnly(FMaterialParameterInfo("DisplacementTexture"), pbrTextures.DISPLACEMENT_TEXTURE); }
	if (pbrTextures.EMISSIVE_TEXTURE != nullptr) { NewMaterialInst->SetTextureParameterValueEditorOnly(FMaterialParameterInfo("EmissiveTexture"), pbrTextures.EMISSIVE_TEXTURE); }
	
	if (pbrTextures.ORM_TEXTURE != nullptr) {
		NewMaterialInst->SetTextureParameterValueEditorOnly(FMaterialParameterInfo("AOTexture"), pbrTextures.ORM_TEXTURE);
		NewMaterialInst->SetTextureParameterValueEditorOnly(FMaterialParameterInfo("MetallicTexture"), pbrTextures.ORM_TEXTURE);
		NewMaterialInst->SetTextureParameterValueEditorOnly(FMaterialParameterInfo("RoughnessTexture"), pbrTextures.ORM_TEXTURE);
	}
	else {

		if (pbrTextures.AO_TEXTURE != nullptr) { NewMaterialInst->SetTextureParameterValueEditorOnly(FMaterialParameterInfo("AOTexture"), pbrTextures.AO_TEXTURE); }
		if (pbrTextures.METALLIC_TEXTURE != nullptr) { NewMaterialInst->SetTextureParameterValueEditorOnly(FMaterialParameterInfo("MetallicTexture"), pbrTextures.METALLIC_TEXTURE); }
		if (pbrTextures.ROUGHNESS_TEXTURE != nullptr) { NewMaterialInst->SetTextureParameterValueEditorOnly(FMaterialParameterInfo("RoughnessTexture"), pbrTextures.ROUGHNESS_TEXTURE); }

	}
	if (pbrTextures.OPACITY_TEXTURE != nullptr) { NewMaterialInst->SetTextureParameterValueEditorOnly(FMaterialParameterInfo("OpacityTexture"), pbrTextures.OPACITY_TEXTURE); }

	//UVLTEditorToolBPLibrary::ShowEditorAlert("Material Has been Created!! " + outputpath);
	//f
	return pbrTextures;
}

TArray<FColor> UVLTET_MaterialHandler_BPLibrary::GetChannelFromTexture(UTexture2D* Source, ETextureChannel TargetChannel)
{
	TextureCompressionSettings OldCompressionSettings = Source->CompressionSettings;
	TextureMipGenSettings OldMipGenSettings = Source->MipGenSettings;
	bool OldSRGB = Source->SRGB;

	Source->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
	Source->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
	Source->SRGB = false;
	Source->UpdateResource();
	TArray<FColor> Pixels;

	const FColor* FormatedImageData = static_cast<const FColor*>(Source->PlatformData->Mips[0].BulkData.LockReadOnly());
	int32 XSize = Source->GetSizeX();
	int32 YSize = Source->GetSizeY();

	for (int32 X = 0; X < XSize; X++)
	{
		for (int32 Y = 0; Y < YSize; Y++)
		{
			FColor PixelColor = FormatedImageData[Y * XSize + X];
			if (TargetChannel == ETextureChannel::R) {
				PixelColor.R = PixelColor.R;
				PixelColor.G = PixelColor.R;
				PixelColor.B = PixelColor.R;
				PixelColor.A = PixelColor.R;

			}
			if (TargetChannel == ETextureChannel::G) {
				PixelColor.R = PixelColor.G;
				PixelColor.G = PixelColor.G;
				PixelColor.B = PixelColor.G;
				PixelColor.A = PixelColor.G;

			}
			if (TargetChannel == ETextureChannel::B) {
				PixelColor.R = PixelColor.B;
				PixelColor.G = PixelColor.B;
				PixelColor.B = PixelColor.B;
				PixelColor.A = PixelColor.A;

			}
			if (TargetChannel == ETextureChannel::A) {
				PixelColor.R = PixelColor.A;
				PixelColor.G = PixelColor.A;
				PixelColor.B = PixelColor.A;
				PixelColor.A = PixelColor.A;

			}
			if (TargetChannel == ETextureChannel::ORIGINAL) {
				PixelColor.R = PixelColor.R;
				PixelColor.G = PixelColor.G;
				PixelColor.B = PixelColor.B;
				PixelColor.A = PixelColor.A;

			}
			if (TargetChannel == ETextureChannel::AVERAGE) {
				float averagee = (PixelColor.R + PixelColor.G + PixelColor.B) / 3;
				PixelColor.R = PixelColor.R;
				PixelColor.G = PixelColor.G;
				PixelColor.B = PixelColor.B;
				PixelColor.A = PixelColor.A;

			}
			if (TargetChannel == ETextureChannel::WHITE) {
				float averagee = (PixelColor.R + PixelColor.G + PixelColor.B) / 3;
				PixelColor.R = 255;
				PixelColor.G = 255;
				PixelColor.B = 255;
				PixelColor.A = 255;

			}
			if (TargetChannel == ETextureChannel::BLACK) {
				float averagee = (PixelColor.R + PixelColor.G + PixelColor.B) / 3;
				PixelColor.R = 0;
				PixelColor.G = 0;
				PixelColor.B = 0;
				PixelColor.A = 0;

			}
			Pixels.Add(PixelColor);
			// Do the job with the pixel
		}
	}

	Source->PlatformData->Mips[0].BulkData.Unlock();

	Source->CompressionSettings = OldCompressionSettings;
	Source->MipGenSettings = OldMipGenSettings;
	Source->SRGB = OldSRGB;
	Source->UpdateResource();

	return Pixels;
}

FPPixelMatrix UVLTET_MaterialHandler_BPLibrary::PixelArrayToPixelMatrix(TArray<FColor> Source, int32 sizeX, int32 sizeY)
{
	FPPixelMatrix outpixelmatrix;

	for (int32 X = 0; X < sizeX; X++)
	{

	 FPPixels YPIXELS;


		for (int32 Y = 0; Y < sizeY; Y++)
		{

			YPIXELS.YPIXELS.Add(Source[Y * sizeX + X]);
		}
		
		outpixelmatrix.XPIXELS.Add(YPIXELS);
	}
	

	return outpixelmatrix;
}

TArray<FColor> UVLTET_MaterialHandler_BPLibrary::PixelMatrixToPixelArray(FPPixelMatrix Source, int32 sizeX, int32 sizeY)
{

	TArray<FColor> Pixels;
	for (int32 X = 0; X < sizeX; X++)
	{
		for (int32 Y = 0; Y < sizeY; Y++)
		{
			FColor PixelColor;
			PixelColor.R = Source.XPIXELS[X].YPIXELS[Y].R;
			PixelColor.G = Source.XPIXELS[X].YPIXELS[Y].G;
			PixelColor.B = Source.XPIXELS[X].YPIXELS[Y].B;
			PixelColor.A = Source.XPIXELS[X].YPIXELS[Y].A;
			Pixels.Add(PixelColor);
		}
	}


	return Pixels;
}

TArray<FColor> UVLTET_MaterialHandler_BPLibrary::CreateSingleColorPixelArray(FColor TargetColor, int32 sizeX, int32 sizeY)
{
	TArray<FColor> Pixels;
	for (int32 X = 0; X < sizeX; X++)
	{
		for (int32 Y = 0; Y < sizeY; Y++)
		{
			FColor PixelColor;
			PixelColor.R = TargetColor.R;
			PixelColor.G = TargetColor.G;
			PixelColor.B = TargetColor.B;
			PixelColor.A = TargetColor.A;
			Pixels.Add(PixelColor);
		}
	}
	return Pixels;
}

bool UVLTET_MaterialHandler_BPLibrary::SaveColorArrayAsPNG(int32 sizeX, int32 sizeY, const TArray<FColor>& bitmapData, const FString& filePath)
{
	TArray<uint8> compressedBitmap;
	FImageUtils::CompressImageArray(sizeX, sizeY, bitmapData, compressedBitmap);
	return FFileHelper::SaveArrayToFile(compressedBitmap, *filePath);
}

bool UVLTET_MaterialHandler_BPLibrary::CheckPixelArrayIfEmpty(const TArray<FColor>& bitmapData)
{
	int32 alphacount = 0;
	for (int32 X = 0; X < bitmapData.Num(); X++)
	{
		if (bitmapData[X].A == 0) {
			alphacount += 1;
		}
	}
	//UE_LOG(LogTemp, Warning, TEXT("Count : %s"), alphacount);
	FString Countt = "Count : " +  FString::FormatAsNumber( alphacount);
	UVLTEditorToolBPLibrary::ShowEditorAlert(Countt, 0.1F, .02F, 2.0F);
	if (alphacount >= bitmapData.Num() - 3) {
		return true;
	}

	return false;
}

FPBRTextures UVLTET_MaterialHandler_BPLibrary::CheckEmptyTexturesInPack(FPBRTextures PBRTextures)
{
	UTexture2D* targetSourceTexture = PBRTextures.ROUGHNESS_TEXTURE;

	// Handle Setting Size
	int32 XSize = 10;
	int32 YSize = 10;

	if (PBRTextures.DIFFUSE_TEXTURE != nullptr) { targetSourceTexture = PBRTextures.DIFFUSE_TEXTURE; 	XSize = PBRTextures.DIFFUSE_TEXTURE->GetSizeX();	YSize = PBRTextures.DIFFUSE_TEXTURE->GetSizeY(); }
	else {
		if (PBRTextures.ROUGHNESS_TEXTURE != nullptr) { targetSourceTexture = PBRTextures.ROUGHNESS_TEXTURE; 	XSize = PBRTextures.ROUGHNESS_TEXTURE->GetSizeX();	YSize = PBRTextures.ROUGHNESS_TEXTURE->GetSizeY(); }
		else {
			if (PBRTextures.METALLIC_TEXTURE != nullptr) { targetSourceTexture = PBRTextures.METALLIC_TEXTURE; XSize = PBRTextures.METALLIC_TEXTURE->GetSizeX();	YSize = PBRTextures.METALLIC_TEXTURE->GetSizeY(); }
			else {
				if (PBRTextures.AO_TEXTURE != nullptr) { targetSourceTexture = PBRTextures.AO_TEXTURE; XSize = PBRTextures.AO_TEXTURE->GetSizeX();	YSize = PBRTextures.AO_TEXTURE->GetSizeY(); }
				else {
					if (PBRTextures.NORMAL_TEXTURE != nullptr) { targetSourceTexture = PBRTextures.NORMAL_TEXTURE; 	XSize = PBRTextures.NORMAL_TEXTURE->GetSizeX();	YSize = PBRTextures.NORMAL_TEXTURE->GetSizeY(); }
					else {
						if (PBRTextures.DISPLACEMENT_TEXTURE != nullptr) { targetSourceTexture = PBRTextures.DISPLACEMENT_TEXTURE; XSize = PBRTextures.DISPLACEMENT_TEXTURE->GetSizeX();	YSize = PBRTextures.DISPLACEMENT_TEXTURE->GetSizeY(); }
						else {
							if (PBRTextures.EMISSIVE_TEXTURE != nullptr) { targetSourceTexture = PBRTextures.EMISSIVE_TEXTURE; XSize = PBRTextures.EMISSIVE_TEXTURE->GetSizeX();	YSize = PBRTextures.EMISSIVE_TEXTURE->GetSizeY(); }

						}
					}

				}
			}
		}
	}

	// Handle Creating of Pixel Arrays
	if (PBRTextures.DIFFUSE_TEXTURE != nullptr) { PBRTextures.PBRTexture_PIXELS.DIFFUSE_PIXELS = UVLTET_MaterialHandler_BPLibrary::GetChannelFromTexture(PBRTextures.DIFFUSE_TEXTURE, ETextureChannel::ORIGINAL); }
	else {

		PBRTextures.PBRTexture_PIXELS.DIFFUSE_PIXELS = UVLTET_MaterialHandler_BPLibrary::CreateSingleColorPixelArray(FColor::Black, XSize, YSize);
	}
	if (PBRTextures.ROUGHNESS_TEXTURE != nullptr) { PBRTextures.PBRTexture_PIXELS.ROUGHNESS_PIXELS = UVLTET_MaterialHandler_BPLibrary::GetChannelFromTexture(PBRTextures.ROUGHNESS_TEXTURE, ETextureChannel::R); }
	else {

		PBRTextures.PBRTexture_PIXELS.ROUGHNESS_PIXELS = UVLTET_MaterialHandler_BPLibrary::CreateSingleColorPixelArray(FColor::Black, XSize, YSize);
	}
	if (PBRTextures.METALLIC_TEXTURE != nullptr) { PBRTextures.PBRTexture_PIXELS.METALLIC_PIXELS = UVLTET_MaterialHandler_BPLibrary::GetChannelFromTexture(PBRTextures.METALLIC_TEXTURE, ETextureChannel::R); }
	else {

		PBRTextures.PBRTexture_PIXELS.METALLIC_PIXELS = UVLTET_MaterialHandler_BPLibrary::CreateSingleColorPixelArray(FColor::Black, XSize, YSize);
	}
	if (PBRTextures.AO_TEXTURE != nullptr) { PBRTextures.PBRTexture_PIXELS.AO_PIXELS = UVLTET_MaterialHandler_BPLibrary::GetChannelFromTexture(PBRTextures.AO_TEXTURE, ETextureChannel::R); }
	else {

		PBRTextures.PBRTexture_PIXELS.AO_PIXELS = UVLTET_MaterialHandler_BPLibrary::CreateSingleColorPixelArray(FColor::Black, XSize, YSize);
	}
	if (PBRTextures.NORMAL_TEXTURE != nullptr) { PBRTextures.PBRTexture_PIXELS.NORMAL_PIXELS = UVLTET_MaterialHandler_BPLibrary::GetChannelFromTexture(PBRTextures.NORMAL_TEXTURE, ETextureChannel::ORIGINAL); }
	else {

		PBRTextures.PBRTexture_PIXELS.NORMAL_PIXELS = UVLTET_MaterialHandler_BPLibrary::CreateSingleColorPixelArray(FColor::Black, XSize, YSize);
	}
	if (PBRTextures.DISPLACEMENT_TEXTURE != nullptr) { PBRTextures.PBRTexture_PIXELS.DISPLACEMENT_PIXELS = UVLTET_MaterialHandler_BPLibrary::GetChannelFromTexture(PBRTextures.DISPLACEMENT_TEXTURE, ETextureChannel::ORIGINAL); }
	else {

		PBRTextures.PBRTexture_PIXELS.DISPLACEMENT_PIXELS = UVLTET_MaterialHandler_BPLibrary::CreateSingleColorPixelArray(FColor::Black, XSize, YSize);
	}
	
	if (PBRTextures.EMISSIVE_TEXTURE != nullptr) { PBRTextures.PBRTexture_PIXELS.EMISSIVE_PIXELS = UVLTET_MaterialHandler_BPLibrary::GetChannelFromTexture(PBRTextures.EMISSIVE_TEXTURE, ETextureChannel::ORIGINAL); }
	else {

		PBRTextures.PBRTexture_PIXELS.EMISSIVE_PIXELS = UVLTET_MaterialHandler_BPLibrary::CreateSingleColorPixelArray(FColor::Black, XSize, YSize);
	}
	if (PBRTextures.OPACITY_TEXTURE != nullptr) { PBRTextures.PBRTexture_PIXELS.OPACITY_PIXELS = UVLTET_MaterialHandler_BPLibrary::GetChannelFromTexture(PBRTextures.OPACITY_TEXTURE, ETextureChannel::ORIGINAL); }
	else {

		PBRTextures.PBRTexture_PIXELS.OPACITY_PIXELS = UVLTET_MaterialHandler_BPLibrary::CreateSingleColorPixelArray(FColor::Black, XSize, YSize);
	}
	
	if (PBRTextures.ORM_TEXTURE != nullptr) { PBRTextures.PBRTexture_PIXELS.ORM_PIXELS = UVLTET_MaterialHandler_BPLibrary::GetChannelFromTexture(PBRTextures.ORM_TEXTURE, ETextureChannel::ORIGINAL); PBRTextures.UseORM = true;	}
	else {
		PBRTextures.UseORM = false;
		PBRTextures.PBRTexture_PIXELS.ORM_PIXELS = UVLTET_MaterialHandler_BPLibrary::CreateSingleColorPixelArray(FColor::Black, XSize, YSize);
	}


	return PBRTextures;
}

FPBRTextures UVLTET_MaterialHandler_BPLibrary::PBRTexturePackFromSelectedAssets()
{
	FString AssetFolder = "";
	TArray<UTexture2D*> Textures;
	TArray<FAssetData> assets = UVLTEditorToolBPLibrary::GetSelectedAssetsInContentBrowser();
	for (auto assett : assets) {
		auto focusasset = assett;
		auto currentasset = focusasset.GetAsset();
		AssetFolder = focusasset.PackagePath.ToString().Replace(TEXT("/Game/"), *UVLTEditorToolBPLibrary::GetGameContentPath());

		Textures.Add(Cast<UTexture2D>(currentasset));
	}


	//FPBRTextures pbrTexturePack = UVLTET_MaterialHandler_BPLibrary::CheckEmptyTexturesInPack(UVLTET_MaterialHandler_BPLibrary::OrganizeTexturesIntoPBRTexturePack(Textures));
	return UVLTET_MaterialHandler_BPLibrary::OrganizeTexturesIntoPBRTexturePack(Textures);
}

TArray<int32> UVLTET_MaterialHandler_BPLibrary::GetTextureDimensionsFromPbrTexturePack(FPBRTextures PBRTextures)
{
	TArray<int32> sizevect;
	// Handle Setting Size
	int32 XSize = 10;
	int32 YSize = 10;
	int32 TextureNum = 10;

	if (PBRTextures.DIFFUSE_TEXTURE != nullptr) { 	XSize = PBRTextures.DIFFUSE_TEXTURE->GetSizeX();	YSize = PBRTextures.DIFFUSE_TEXTURE->GetSizeY(); }
	else {
		if (PBRTextures.ROUGHNESS_TEXTURE != nullptr) { 	XSize = PBRTextures.ROUGHNESS_TEXTURE->GetSizeX();	YSize = PBRTextures.ROUGHNESS_TEXTURE->GetSizeY(); }
		else {
			if (PBRTextures.METALLIC_TEXTURE != nullptr) { XSize = PBRTextures.METALLIC_TEXTURE->GetSizeX();	YSize = PBRTextures.METALLIC_TEXTURE->GetSizeY(); }
			else {
				if (PBRTextures.AO_TEXTURE != nullptr) {  XSize = PBRTextures.AO_TEXTURE->GetSizeX();	YSize = PBRTextures.AO_TEXTURE->GetSizeY(); }
				else {
					if (PBRTextures.NORMAL_TEXTURE != nullptr) {  	XSize = PBRTextures.NORMAL_TEXTURE->GetSizeX();	YSize = PBRTextures.NORMAL_TEXTURE->GetSizeY(); }
					else {
						if (PBRTextures.DISPLACEMENT_TEXTURE != nullptr) {  XSize = PBRTextures.DISPLACEMENT_TEXTURE->GetSizeX();	YSize = PBRTextures.DISPLACEMENT_TEXTURE->GetSizeY(); }
						else {
							if (PBRTextures.EMISSIVE_TEXTURE != nullptr) {  XSize = PBRTextures.EMISSIVE_TEXTURE->GetSizeX();	YSize = PBRTextures.EMISSIVE_TEXTURE->GetSizeY(); }

						}
					}

				}
			}
		}
	}
	sizevect.Add(XSize);
	sizevect.Add(YSize);
	return sizevect;
}


bool UVLTET_MaterialHandler_BPLibrary::CreatePackedTextureORMFromTextures(UTexture2D* OcclusionTexture, UTexture2D* RoughnessTexture, UTexture2D* MetallicTexture, const FString& filePath)
{


	int32 XSize = RoughnessTexture->GetSizeX();
	int32 YSize = RoughnessTexture->GetSizeY();
	if (OcclusionTexture->GetSizeX() != XSize) { return false; }
	if (MetallicTexture->GetSizeX() != XSize) { return false; }

	TArray<FColor> AOTex = UVLTET_MaterialHandler_BPLibrary::GetChannelFromTexture(OcclusionTexture, ETextureChannel::R);
	TArray<FColor> RoughnessTex = UVLTET_MaterialHandler_BPLibrary::GetChannelFromTexture(RoughnessTexture, ETextureChannel::R);
	TArray<FColor> MetallicTex = UVLTET_MaterialHandler_BPLibrary::GetChannelFromTexture(MetallicTexture, ETextureChannel::R);

	if (UVLTET_MaterialHandler_BPLibrary::CheckPixelArrayIfEmpty(AOTex) ) { UVLTEditorToolBPLibrary::ShowEditorAlert("AO TEX EMPTY", 0.1F, .02F, 2.0F)  ; return false; }
	if (UVLTET_MaterialHandler_BPLibrary::CheckPixelArrayIfEmpty(RoughnessTex) ) { UVLTEditorToolBPLibrary::ShowEditorAlert("METALLIC ROUGHNESS EMPTY", 0.1F, .02F, 2.0F); return false; }
	if (UVLTET_MaterialHandler_BPLibrary::CheckPixelArrayIfEmpty(MetallicTex) ) { UVLTEditorToolBPLibrary::ShowEditorAlert("METALLIC TEX EMPTY",0.1F,.02F, 2.0F ) ;  return false; }

	TArray<FColor> OutputPixels ;

	for (int32 X = 0; X < AOTex.Num() ; X++)
	{
		FColor PixelColor = FColor::Black;
			PixelColor.R = AOTex[X].R;
			PixelColor.G = RoughnessTex[X].G;
			PixelColor.B = MetallicTex[X].B;
			OutputPixels.Add(PixelColor);
	}

	
			//GetChannelFromTexture

	return UVLTET_MaterialHandler_BPLibrary::SaveColorArrayAsPNG(XSize, YSize, OutputPixels, filePath);
}

bool UVLTET_MaterialHandler_BPLibrary::CreatePackedTextureORMFromColorArray(const TArray<FColor>& OcclusionTexture, const TArray<FColor>& RoughnessTexture, const TArray<FColor>& MetallicTexture, int32 sizeX, int32 sizeY, const FString& filePath)
{



	int32 XSize = sizeX;
	int32 YSize = sizeY;


	TArray<FColor> OutputPixels;

	for (int32 X = 0; X < OcclusionTexture.Num(); X++)
	{
		FColor PixelColor = FColor::Black;
		PixelColor.R = OcclusionTexture[X].R;
		PixelColor.G = RoughnessTexture[X].G;
		PixelColor.B = MetallicTexture[X].B;
		OutputPixels.Add(PixelColor);
	}


	//GetChannelFromTexture

	return UVLTET_MaterialHandler_BPLibrary::SaveColorArrayAsPNG(XSize, YSize, OutputPixels, filePath);
}

bool UVLTET_MaterialHandler_BPLibrary::CreatePackedTextureORMFromPBRTexturePack(FPBRTextures PbrTexturePack, const FString& filePath)
{
	TArray<int32>  SizeArray = UVLTET_MaterialHandler_BPLibrary::GetTextureDimensionsFromPbrTexturePack(PbrTexturePack);
	int32 XSize = SizeArray[0];
	int32 YSize = SizeArray[1];


	TArray<FColor> OutputPixels;

	for (int32 X = 0; X < PbrTexturePack.PBRTexture_PIXELS.DIFFUSE_PIXELS.Num(); X++)
	{
		FColor PixelColor = FColor::Black;
		PixelColor.R = PbrTexturePack.PBRTexture_PIXELS.AO_PIXELS[X].R;
		PixelColor.G = PbrTexturePack.PBRTexture_PIXELS.ROUGHNESS_PIXELS[X].G;
		PixelColor.B = PbrTexturePack.PBRTexture_PIXELS.METALLIC_PIXELS[X].B;
		OutputPixels.Add(PixelColor);
	}
	TArray<FColor> TempOutputPixels = UVLTET_MaterialHandler_BPLibrary::PixelMatrixToPixelArray( UVLTET_MaterialHandler_BPLibrary::PixelArrayToPixelMatrix(OutputPixels, XSize, YSize), XSize, YSize);



	//GetChannelFromTexture

	return UVLTET_MaterialHandler_BPLibrary::SaveColorArrayAsPNG(XSize, YSize, TempOutputPixels, filePath);

}

UTexture2D* UVLTET_MaterialHandler_BPLibrary::ChannelFromTextureToTexture(UTexture2D* Source, ETextureChannel TargetChannel, const bool UseAlpha)
{
	TextureCompressionSettings OldCompressionSettings = Source->CompressionSettings;
	TextureMipGenSettings OldMipGenSettings = Source->MipGenSettings;
	bool OldSRGB = Source->SRGB;

	Source->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
	Source->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
	Source->SRGB = false;
	Source->UpdateResource();
	TArray<FColor> Pixels;

	const FColor* FormatedImageData = static_cast<const FColor*>(Source->PlatformData->Mips[0].BulkData.LockReadOnly());
	int32 XSize = Source->GetSizeX();
	int32 YSize = Source->GetSizeY();
	for (int32 X = 0; X < XSize; X++)
	{
		for (int32 Y = 0; Y < YSize; Y++)
		{
			FColor PixelColor = FormatedImageData[Y * XSize + X];
			PixelColor.B = PixelColor.R;
			PixelColor.G = PixelColor.R;
			
			Pixels.Add(PixelColor);
			// Do the job with the pixel
		}
	}

	Source->PlatformData->Mips[0].BulkData.Unlock();

	Source->CompressionSettings = OldCompressionSettings;
	Source->MipGenSettings = OldMipGenSettings;
	Source->SRGB = OldSRGB;
	Source->UpdateResource();
	
	UTexture2D* texture = UTexture2D::CreateTransient(XSize, YSize, PF_FloatRGB);
	void* TextureData = texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(TextureData, &Pixels, 3 * XSize * YSize);
	texture->PlatformData->Mips[0].BulkData.Unlock();
	texture->UpdateResource();



	return texture;
}
