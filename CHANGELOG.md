# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Released]

## [1.0.0] - 2021-06-08
- Initial original version currently running.

## [1.0.1] - 2021-06-13

### UVLTET_MaterialHandler_BPLibrary

- Function <u>GetChannelFromTexture</u>
  - Get a specific channel from a Texture2D as a ```TArray<FColor>```
- Struct <u>ETextureChannel</u>
  - R,G,B struct, just makes it easier to move info around.
- Function <u>ChannelFromTextureToTexture</u> (bugged)
  - Get a specific channel from a Texture2D, then create a new Texture2D from that channel and return it as a ```UTexture2D```.
- Function <u>CreatePackedTextureORMFromTextures</u>
  - Create a packed .png texture file at the specified.  Packed in the format of: R = AmbientOcclusion, G = Roughness, B = Metallic 
-  Function <u>CreatePackedTextureORMFromColorArray</u>
  - Create a packed .png texture file at the specified from a FColor Array.  Packed in the format of: R = AmbientOcclusion, G = Roughness, B = Metallic 
- Function <u>Check Pixel Array If Empty</u>
  - Check if a Pixel Array is empty by iterating over the alpha and checking if it's always 0.
- Function <u>OrganizeTexturesIntoPBRTexturePack</u>
  - Organize  textures into PBR texture pack struct.
- Function CreatePackedTextureORMFromSelectedTextures
  - Create a packed .png texture file in the same folder as the first asset provided.  Packed in the format of: R = AmbientOcclusion, G = Roughness, B = Metallic 
- Function CreatePackedTextureORMFromPBRTexturePack
  - Create a packed .png texture file in the same folder as the first asset provided.  Packed in the format of: R = AmbientOcclusion, G = Roughness, B = Metallic 
- Function [<u>CreateSingleColorPixelArray</u>]()
  - Create a FColor array that only contains the target color.
- Function <u>CheckEmptyTexturesInPack</u>
  - Check for empty textures in PBR Texture pack Struct.

- Function <u>GetTextureDimensionsFromPbrTexturePack</u>
  - Get the File size from a non empty texture in a  PBR Texture pack Struct.
