// Copyright Epic Games, Inc. All Rights Reserved.

#include "VLTEditorToolBPLibrary.h"
#include "VLTEditorTool.h"
#include "Engine/Selection.h"
#include "IContentBrowserSingleton.h"
#include "ContentBrowserModule.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Framework/Notifications/NotificationManager.h"
#include "EditorStyleSet.h"
#include "Brushes/SlateImageBrush.h"
#include "Misc/Paths.h"
#define LOCTEXT_NAMESPACE "AssetTypeActions"




UVLTEditorToolBPLibrary::UVLTEditorToolBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}


void UVLTEditorToolBPLibrary::CopyDirectoryToDirectory(FString Source, FString Target, bool Overwrite)
{
	IPlatformFile& F = FPlatformFileManager::Get().GetPlatformFile();
	F.CopyDirectoryTree(*Target, *Source, Overwrite);
    




}

void UVLTEditorToolBPLibrary::CopyFileToFile(FString Source, FString Target)
{

    IPlatformFile& F = FPlatformFileManager::Get().GetPlatformFile();
    F.CopyFile(*Target, *Source, EPlatformFileRead::AllowWrite);

}

FString UVLTEditorToolBPLibrary::RelativePathToFullPath(FString Source)
{

    IPlatformFile& F = FPlatformFileManager::Get().GetPlatformFile();
    return F.ConvertToAbsolutePathForExternalAppForRead(*Source);
}





// Undefine the namespace before the end of the file
TArray<FString> UVLTEditorToolBPLibrary::GetSelectedFolderInContentBrowser()
{

    TArray<FString> Folders;
    TArray<FString> results;
    FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
    IContentBrowserSingleton& ContentBrowserSingleton = ContentBrowserModule.Get();
    ContentBrowserSingleton.GetSelectedFolders(Folders);
    return Folders;
}

TArray<FAssetData> UVLTEditorToolBPLibrary::GetSelectedAssetsInContentBrowser()
{

    TArray<FString> Folders;
    TArray<FAssetData> results;
    FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
    IContentBrowserSingleton& ContentBrowserSingleton = ContentBrowserModule.Get();
    ContentBrowserSingleton.GetSelectedAssets(results);
    return results;
}

TArray<AActor*> UVLTEditorToolBPLibrary::GetSelectedActorsInScene()
{
    USelection* SelectedActors = GEditor->GetSelectedActors();
    TArray<AActor*> Actors;
    for (FSelectionIterator Iter(*SelectedActors); Iter; ++Iter)
    {
        AActor* Actor = Cast<AActor>(*Iter);
        if (Actor)
        {
            Actors.Add(Actor);
            //UniqueLevels.AddUnique(Actor->GetLevel());
        }
    }
    return Actors;
}

void UVLTEditorToolBPLibrary::SelectActorInEditor()
{
    USelection* SelectedActors = GEditor->GetSelectedActors();
    TArray<AActor*> Actors;
    for (FSelectionIterator Iter(*SelectedActors); Iter; ++Iter)
    {
        AActor* Actor = Cast<AActor>(*Iter);
        if (Actor)
        {
            Actors.Add(Actor);
            //UniqueLevels.AddUnique(Actor->GetLevel());
        }
    }
}

AActor* UVLTEditorToolBPLibrary::GetSelectedActorInScene()
{
    USelection* SelectedActors = GEditor->GetSelectedActors();
    TArray<AActor*> Actors;
    for (FSelectionIterator Iter(*SelectedActors); Iter; ++Iter)
    {
        AActor* Actor = Cast<AActor>(*Iter);
        if (Actor)
        {
            Actors.Add(Actor);
            //UniqueLevels.AddUnique(Actor->GetLevel());
        }
    }
    AActor* Actor = Actors[0];

    return Actor;
}

AActor* UVLTEditorToolBPLibrary::GetSelectedActorInSceneByIndex(int32 index)
{
    USelection* SelectedActors = GEditor->GetSelectedActors();
    TArray<AActor*> Actors;
    for (FSelectionIterator Iter(*SelectedActors); Iter; ++Iter)
    {
        AActor* Actor = Cast<AActor>(*Iter);
        if (Actor)
        {
            Actors.Add(Actor);
            //UniqueLevels.AddUnique(Actor->GetLevel());
        }
    }
    AActor* Actor = Actors[index];
    return Actor;
}

void UVLTEditorToolBPLibrary::ShowEditorAlert(FString message, float FadeInDuration, float FadeoutDuration, float ExpireDuration)
{

    FFormatNamedArguments Arguments;
    Arguments.Add("message", FText::FromString(message));
    const FText messagetext = FText::Format(LOCTEXT("PlaceItem", "{message}"), Arguments);
    FNotificationInfo Info(messagetext);
    Info.Image = FEditorStyle::GetBrush(TEXT("LevelEditor.RecompileGameCode"));
    Info.FadeInDuration = FadeInDuration;
    Info.FadeOutDuration = FadeoutDuration;
    Info.ExpireDuration = ExpireDuration;
    Info.bUseThrobber = false;
    Info.bUseSuccessFailIcons = true;
    Info.bUseLargeFont = true;
    Info.bFireAndForget = false;
    Info.bAllowThrottleWhenFrameRateIsLow = false;
    auto NotificationItem = FSlateNotificationManager::Get().AddNotification(Info);
    NotificationItem->SetCompletionState(SNotificationItem::CS_Success);
    NotificationItem->ExpireAndFadeout();

    //GEditor->PlayEditorSound(CompileSuccessSound);
}

FSlateBrush UVLTEditorToolBPLibrary::FSlateImageFromAssetPath(FString AssetPath, int64 width, int64 height)
{
    FString PathToImage = AssetPath;

    FString ImagePath = FPaths::ProjectContentDir() / PathToImage;
    FName BrushName = FName(*ImagePath);
    return FSlateImageBrush(BrushName, FVector2D(width, height));
}

FString UVLTEditorToolBPLibrary::GetGameContentPath()
{

    return FPaths::ProjectContentDir();
}


#undef LOCTEXT_NAMESPACE