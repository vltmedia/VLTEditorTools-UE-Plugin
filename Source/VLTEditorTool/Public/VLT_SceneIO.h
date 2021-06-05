// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VLT_SceneIO.generated.h"



/**
 *
 */

USTRUCT(BlueprintType)
struct FVLT_Transform
{
    GENERATED_BODY()
        UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<float> Position;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<float> Rotation;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<float> Scale;
    FVLT_Transform() {
             Position = {0,0,0};
             Rotation = {0,0,0};
             Scale = {0,0,0};

    }

};

USTRUCT(BlueprintType)
struct FVLT_BaseObject {
    GENERATED_BODY()
        UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString Category;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FVLT_Transform Transform;

    FVLT_BaseObject() {
        Name = FString(TEXT(""));
        Category = FString(TEXT(""));
        Transform = FVLT_Transform();

    }

};

USTRUCT(BlueprintType)
struct FVLT_Scene
{
    GENERATED_BODY()
        UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<FVLT_BaseObject> Objects;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<FString> Categories;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32  Count;
    FVLT_Scene() {
        Objects = {};
        Categories = {};
        Count = 0;

    }


};


/**
 * 
 */
UCLASS()
class VLTEDITORTOOL_API UVLT_SceneIO : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

public:


    // declare mesh component
    UPROPERTY(VisibleAnywhere);
    class UStaticMeshComponent* MyMesh;

    UFUNCTION(BlueprintCallable, Category = "VLT - Pipeline")
        static FString ReadTextFromFile(FString filepath);

    UFUNCTION(BlueprintCallable, Category = "VLT - Pipeline")
        static FVLT_Scene LoadFromFilepath(FString filepath);

    UFUNCTION(BlueprintCallable, Category = "VLT - Conversion")
        static FVector  XYZToUEPosition(float pX, float pY, float pZ, float ScaleMult);

    UFUNCTION(BlueprintCallable, Category = "VLT - Conversion")
        static FTransform  XYZToUETransform(float pX, float pY, float pZ, float sX, float sY, float sZ, float rX, float rY, float rZ, float SceneMult);

    UFUNCTION(BlueprintCallable, Category = "VLT - Conversion")
        static FTransform  XYZFArraysToUETransform(TArray<float>Position, TArray<float>Rotation, TArray<float>Scale, float SceneMult);

    UFUNCTION(BlueprintCallable, Category = "VLT - Conversion")
        static FTransform  XYZFVectorsToUETransform(FVector Position, FVector Rotation, FVector Scale, float SceneMult);

    UFUNCTION(BlueprintCallable, Category = "VLT - Conversion")
        static FTransform  VLTBaseObjectXYZToUETransform(FVLT_BaseObject VLT_BaseObject, float SceneMult);


    UFUNCTION(BlueprintCallable, Category = "VLT - Conversion")
        static FRotator  HPBToUERotator(float H, float P, float B);

};
