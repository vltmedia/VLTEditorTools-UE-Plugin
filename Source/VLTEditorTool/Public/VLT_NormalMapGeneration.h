// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <stdint.h>
#include "IImageWrapperModule.h"
#include "Math/Color.h"
#include "ImageUtils.h"


//#include "stb_image.h" 


#include "EditorFramework/AssetImportData.h"
#include "VLT_NormalMapGeneration.generated.h"
//#define ENUM_EACH(PARAM) PARAM,
//#define STR_EACH(PARAM) #PARAM,
//#define STR_EACH_SEP_WS(PARAM) #PARAM " "
//
//#define EACH_FILTER_TYPE(DO) \
//    DO(FILTER_NONE) \
//    DO(FILTER_SOBEL_3x3) \
//    DO(FILTER_SOBEL_5x5) \
//    DO(FILTER_PREWITT_3x3) \
//    DO(FILTER_PREWITT_5x5) \
//    DO(FILTER_3x3) \
//    DO(FILTER_5x5) \
//    DO(FILTER_7x7) \
//    DO(FILTER_9x9) \
//    DO(MAX_FILTER_TYPE)
//#define EFILTER_TYPE_COUNT (10)

UENUM(BlueprintType)
enum EFILTER_TYPE { FILTER_NONE,
    FILTER_SOBEL_3x3,
    FILTER_SOBEL_5x5,
    FILTER_PREWITT_3x3,
    FILTER_PREWITT_5x5,
    FILTER_3x3,
    FILTER_5x5,
    FILTER_7x7,
    FILTER_9x9,
    MAX_FILTER_TYPE
};


UENUM(BlueprintType)
enum EALPHA_TYPE
{
    ALPHA_NONE, ALPHA_HEIGHT, ALPHA_INVERSE_HEIGHT, ALPHA_ZERO, ALPHA_ONE,
    ALPHA_INVERT, ALPHA_MAP, MAX_ALPHA_TYPE
};

UENUM(BlueprintType)
enum ECONVERSION_TYPE
{
    CONVERT_NONE, CONVERT_BIASED_RGB, CONVERT_RED, CONVERT_GREEN,
    CONVERT_BLUE, CONVERT_MAX_RGB, CONVERT_MIN_RGB, CONVERT_COLORSPACE,
    CONVERT_NORMALIZE_ONLY, CONVERT_DUDV_TO_NORMAL, CONVERT_HEIGHTMAP,
    CONVERT_KEY_RGB,
    MAX_CONVERSION_TYPE
};

UENUM(BlueprintType)
enum EDUDV_TYPE
{
    DUDV_NONE, DUDV_8BIT_SIGNED, DUDV_8BIT_UNSIGNED, DUDV_16BIT_SIGNED,
    DUDV_16BIT_UNSIGNED,
    MAX_DUDV_TYPE
};

USTRUCT(BlueprintType)
struct Fkernel_element
{
    GENERATED_BODY()
    int x, y;
    float w;
} ;

USTRUCT(BlueprintType)
struct FNormalmapVals
{
    GENERATED_BODY()
        UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 filter;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float minz;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float scale;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 wrap;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 height_source;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 alpha;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 conversion;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 dudv;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 xinvert;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 yinvert;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 swapRGB;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float contrast;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 alphamap_id;
};
static char* FILTER_TYPE_NAMES[10] = {
    "FILTER_NONE",
    "FILTER_SOBEL_3x3",
    "FILTER_SOBEL_5x5",
    "FILTER_PREWITT_3x3",
    "FILTER_PREWITT_5x5",
    "FILTER_3x3",
    "FILTER_5x5",
    "FILTER_7x7",
    "FILTER_9x9",
    "MAX_FILTER_TYPE"
};
/**
 * 
 */


UCLASS()
class VLTEDITORTOOL_API UVLT_NormalMapGeneration : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
    FNormalmapVals NormalVals;

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Generate NormalMap From Texture", Keywords = "VLTEditorTool Generate NormalMap From Texture"), Category = "VLT - Normal Material Texture IO")
        static      bool GenerateNormalMap(UTexture2D* SourceImage);

    static    bool ConvertToNormalMap(uint8_t* img, uint8_t* nm_img, int32 width, int32 height, FNormalmapVals nmapvals);

    static void scale_pixels(unsigned char* dst, int dw, int dh, unsigned char* src, int sw, int sh, int bpp);

    static int icerp(int a, int b, int c, int d, int x);
    static int sample_alpha_map(unsigned char* pixels, int x, int y, int w, int h, int sw, int sh);


    static inline void NORMALIZE(float* v);

    static void make_kernel(Fkernel_element* k, float* weights, int size);

    static void rotate_array(float* dst, float* src, int size);


    static void make_heightmap(unsigned char* image, int w, int h, int bpp, FNormalmapVals nmapvals);


	
};
