# UE Plugin - VLT Editor Tools
<br>
<img alt="Unreal Engine" src="https://img.shields.io/badge/unrealengine-%23313131.svg?style=for-the-badge&logo=unrealengine&logoColor=white"/>

<a href="https://github.com/vltmedia/VLTEditorTools-UE-Plugin"><img alt="GitHub" src="https://img.shields.io/badge/github-%23121011.svg?style=for-the-badge&logo=github&logoColor=white" /></a>

Editor tools created by VLT Media including local file io, layout tools, and other Quality of Life tools.

# Install
Copy the VLTEditorTool folder into your Unreal Engine project's Plugins folder. When asked to rebuild click Yes or Ok.

# Editor UI Windows
- [Material Wizard EUI](https://vltwiki.com/en/plugins-scripts/ue/VLTEditorTools/MaterialwizardEUI)
- [Copy Dir to Game Dirs](https://vltwiki.com/en/plugins-scripts/ue/VLTEditorTools/CopyDirtoGameDirs)
- [Swap Objects](https://vltwiki.com/en/plugins-scripts/ue/VLTEditorTools/SwapObjects)

# Download
- [v1.0.0 06/05/21](https://www.dropbox.com/s/hb8j3bcdidv2l8e/VLTEditorTool_v1-0-0_210605.zip?dl=0)

# Main Documentation

[UE Plugin - VLT Editor Tools | VLT Wiki](https://vltwiki.com/en/plugins-scripts/ue/VLTEditorTools)

# Material Wizard EUI

![materialwizardeui.png](https://vltwiki.com/images/materialwizardeuiv1.2.0.png)
An Editor UI Window that will help a user select a group of textures, then turn them into a ready to use PBR material instance.

# Path
Right-click the asset and click ```Run Editor Widget Utility```
```/VLTEditorTool/VLTPipe/EUI/EUI_VLTPipe_MaterialImporter.EUI_VLTPipe_MaterialImporter```

# Usage
1. Select multiple Texture Assets in the Content Browser you want to create a material with.

2. Click the Process To Material button to create a Material in the current directory.

An Opaque PBR or Opacity Mask PBR material will be created.

# Approved Naming Conventions

These will be the strings that the different textures will be compared against.

| Name             | Approve Names                          |
| ---------------- | -------------------------------------- |
| Diffuse          | Diffuse,BaseColor                      |
| Roughness        | Roughness,Rough                        |
| Normal           | Normal,_n,norm                         |
| Metallic         | Metallic,Metalness,Metal               |
| Emissive         | Emissive,Emission,Emit                 |
| AmbientOcclusion | AmbientOcclusion,_AO,Ambient,Occlusion |
| Displacement     | Displacement,Height,PixelOffset        |
| Opacity          | Opacity,Transparancy                   |



# Copy Directory to Game Directories EUI
![eui_swap_object.png](https://vltwiki.com/images/eui_copydirectorytogamedirs.png)

A Editor window to help copy a directory on your filesystem to one of your game directories like Content and Plugins. 

# Usage
1. Put a full filepath to a file on your computer into the text input field.
2. Click one of the buttons to copy the entire directory to your selected game directory.



# Swap Objects EUI
![eui_swap_object.png](https://vltwiki.com/images/eui_swap_object.png)
An Editor Window to help swap objects in a scene with another, and keeping them in order.

# Path
Right-click the asset and click ```Run Editor Widget Utility```
```/VLTEditorTool/VLTPipe/EUI/EUI_VLTPipe_SwapObjects.EUI_VLTPipe_SwapObjects```

# Usage
1. If you don't have a ```BP_VLTP_LevelPlacementManager``` in your scene, click the ```Spawn``` button that would be present. Otherwise the checkbox should be checked.
2. Select an **ACTOR** in the scene that you want to clone.
3. Click the ```Focus Selected Object In Scene``` button to focus on that obejct.
4. Select the objects you want to replace.
5. Set a Category Name for the objects. This just helps group things.
6. Set the Scale in the ```Spawn Transform``` menu.
7. Click the ```Replace Selected Objects With Focused Object``` button to replace the selected objects with your focused object.


Use the menu on the right to handle cleaning up Categories if needed.



# UVLTET_MaterialHandler_BPLibrary

This is a Blueprint Library holding a lot of functions to help out in creating new materials and handling textures.

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

- Function <u>PBRTexturePackFromSelectedAssets</u>
  - Get PBR Texture Pack From the Selected Assets in a content browser.
