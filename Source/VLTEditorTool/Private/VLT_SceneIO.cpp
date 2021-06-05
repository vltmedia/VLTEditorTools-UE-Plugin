#include "VLT_SceneIO.h"

// Fill out your copyright notice in the Description page of Project Settings.
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <Runtime\JsonUtilities\Public\JsonObjectConverter.h>








FString UVLT_SceneIO::ReadTextFromFile(FString filepath)
{
	std::string filestd = std::string(TCHAR_TO_UTF8(*filepath));
	std::string  line;
	std::string  data;
	std::ifstream file(filestd);
	std::stringstream str;
	if (file.is_open())
	{
																		 
		while (file.peek() != EOF)
		{
			str << (char)file.get();
		}
		file.close();

	}
	return FString(UTF8_TO_TCHAR(str.str().c_str()));
}

FVLT_Scene UVLT_SceneIO::LoadFromFilepath(FString filepath)
{
	std::string filestd = std::string(TCHAR_TO_UTF8(*filepath));
	std::string  line;
	std::string  data;
	std::ifstream file(filestd);
	std::stringstream str;
	if (file.is_open())
	{
		while (file.peek() != EOF)
		{
			str << (char)file.get();
		}
		file.close();

	}
	FString OutJs = FString(UTF8_TO_TCHAR(str.str().c_str()));
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *OutJs);
	FVLT_Scene OutScene;
	TSharedRef<FJsonObject> JsonData = MakeShareable(new FJsonObject);;
	FJsonObjectConverter::JsonObjectStringToUStruct<FVLT_Scene>(OutJs, &OutScene, 0, 0);
	return  OutScene;

}

FVector UVLT_SceneIO::XYZToUEPosition(float pX, float pY, float pZ, float ScaleMult)
{
	FVector Position;               // Translation

// ************************************************************************************
// Conversion XSI Coordinate System to UE4 Coordinate System

// Position - Swap Z and Y axis and correct Position Scaling

	Position.X = pX * ScaleMult;
	Position.Y = pZ * ScaleMult;
	Position.Z = pY * ScaleMult;
	return Position;
}

FTransform UVLT_SceneIO::XYZToUETransform(float pX, float pY, float pZ, float sX, float sY, float sZ, float rX, float rY, float rZ, float SceneMult)
{
	float rad = 0.0174532925199444; // FQuat needs Radians. So degree * Pi/180 | Pi/180 = 0.0174532...

	// Transform
	FVector Scale(sX, sY, sZ);      // Scale
	FVector Position;               // Translation

	// ************************************************************************************
	// Conversion XSI Coordinate System to UE4 Coordinate System

	// Position - Swap Z and Y axis and correct Position Scaling

	Position.X = pX * SceneMult;
	Position.Y = pZ * SceneMult;
	Position.Z = pY * SceneMult;

	// Quaternions - Convert Rotations from XSI to UE4

	FQuat qx(FVector(1, 0, 0), -rX * rad);
	FQuat qz(FVector(0, 0, 1), -rY * rad);
	FQuat qy(FVector(0, 1, 0), -rZ * rad);

	FQuat qu = qy * qz * qx; // Change Rotation Order if necessary

	FRotator Rotation(qu);
	FTransform Transform(Rotation, Position, Scale);
	return Transform;
}

FTransform UVLT_SceneIO::XYZFArraysToUETransform(TArray<float> Position, TArray<float> Rotation, TArray<float> Scale, float SceneMult)
{
	float rad = 0.0174532925199444; // FQuat needs Radians. So degree * Pi/180 | Pi/180 = 0.0174532...

	// Transform
	FVector Scale_(Scale[0] * SceneMult, Scale[1] * SceneMult, Scale[2] * SceneMult);      // Scale

	FVector Position_;               // Translation

	// ************************************************************************************
	// Conversion XSI Coordinate System to UE4 Coordinate System

	// Position - Swap Z and Y axis and correct Position Scaling

	Position_.X = Position[0] * SceneMult;
	Position_.Y = Position[2] * SceneMult;
	Position_.Z = Position[1] * SceneMult;

	// Quaternions - Convert Rotations from XSI to UE4

	FQuat qx(FVector(1, 0, 0), -Rotation[0] * rad);
	FQuat qz(FVector(0, 0, 1), -Rotation[1] * rad);
	FQuat qy(FVector(0, 1, 0), -Rotation[2] * rad);

	FQuat qu = qy * qz * qx; // Change Rotation Order if necessary

	FRotator Rotation_(qu);
	FTransform Transform(Rotation_, Position_, Scale_);
	return Transform;
}

FTransform UVLT_SceneIO::XYZFVectorsToUETransform(FVector Position, FVector Rotation, FVector Scale, float SceneMult)
{
	float rad = 0.0174532925199444; // FQuat needs Radians. So degree * Pi/180 | Pi/180 = 0.0174532...

// Transform
	FVector Scale_(Scale[0] * SceneMult, Scale[1] * SceneMult, Scale[2] * SceneMult);      // Scale
	FVector Position_;               // Translation

	// ************************************************************************************
	// Conversion XSI Coordinate System to UE4 Coordinate System

	// Position - Swap Z and Y axis and correct Position Scaling

	Position_.X = Position[0] * SceneMult;
	Position_.Y = Position[2] * SceneMult;
	Position_.Z = Position[1] * SceneMult;

	// Quaternions - Convert Rotations from XSI to UE4

	FQuat qx(FVector(1, 0, 0), -Rotation[0] * rad);
	FQuat qz(FVector(0, 0, 1), -Rotation[1] * rad);
	FQuat qy(FVector(0, 1, 0), -Rotation[2] * rad);

	FQuat qu = qy * qz * qx; // Change Rotation Order if necessary

	FRotator Rotation_(qu);
	FTransform Transform(Rotation_, Position_, Scale_);
	return Transform;
}

FTransform UVLT_SceneIO::VLTBaseObjectXYZToUETransform(FVLT_BaseObject VLT_BaseObject, float SceneMult)
{
	float rad = 0.0174532925199444; // FQuat needs Radians. So degree * Pi/180 | Pi/180 = 0.0174532...
	TArray<float>  Position = VLT_BaseObject.Transform.Position;
	TArray<float>  Rotation = VLT_BaseObject.Transform.Rotation;
	TArray<float>  Scale = VLT_BaseObject.Transform.Scale;

	// Transform
	FVector Scale_(Scale[0] * SceneMult, Scale[1] * SceneMult, Scale[2] * SceneMult);      // Scale
	FVector Position_;               // Translation

	// ************************************************************************************
	// Conversion XSI Coordinate System to UE4 Coordinate System

	// Position - Swap Z and Y axis and correct Position Scaling

	Position_.X = -Position[0] * SceneMult;
	Position_.Y = Position[2] * SceneMult;
	Position_.Z = Position[1] * SceneMult;

	// Quaternions - Convert Rotations from XSI to UE4

	FQuat qx(FVector(1, 0, 0), -Rotation[0] * rad);
	FQuat qz(FVector(0, 0, 1), -Rotation[1] * rad);
	FQuat qy(FVector(0, 1, 0), -Rotation[2] * rad);

	FQuat qu = qy * qz * qx; // Change Rotation Order if necessary

	FRotator Rotation_(qu);
	FTransform Transform(Rotation_, Position_, Scale_);
	return Transform;
}

FRotator UVLT_SceneIO::HPBToUERotator(float H, float P, float B)
{
	float rad = 0.0174532925199444; // FQuat needs Radians. So degree * Pi/180 | Pi/180 = 0.0174532...
	// Quaternions - Convert Rotations from XSI to UE4

	FQuat qx(FVector(1, 0, 0), -H * rad);
	FQuat qz(FVector(0, 0, 1), -P * rad);
	FQuat qy(FVector(0, 1, 0), -B * rad);

	FQuat qu = qy * qz * qx; // Change Rotation Order if necessary

	FRotator Rotation(qu);




	return Rotation;
}
