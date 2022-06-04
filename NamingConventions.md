# Naming Conventions
We follow industry-standard naming conventions.



## Source Files
Source files made up of C++ classes and header files.

### Base Classes
Module's base classes of another module's classes.
A[Module Prefix]Character
A[Module Prefix]GameMode
U[Module Prefix]GameplayAbility

### Child Classes
Module's child class variants of its base classes.
A[Module Prefix]Character_[Character Name]
A[Module Prefix]GameMode_[GameMode Name]
U[Module Prefix]GameplayAbility_[GameplayAbility Name]


## Content Files
Content files made up of blueprint classes and other assets.

### Blueprint Classes
Blueprint classes based on native C++ classes.
C_[Character Name]
GM_[GameMode Name]
GA_[GameplayAbility Name]

### Assets
General content assets.
L_[Level Name]
M_[Material Name]
MI_[MaterialInstance Name]
T_[Texture Name]
ABP_[AnimBP Name]
SK_[Skeleton Name]
SKM_[SkeletalMesh Name]
AM_[AnimMontage Name]
BS_[BlendSpace Name]
DT_[DataTable Name]

### Texture Asset Suffixes
Texture assets use suffixes to specify the kind of texture map.
T_[Texture Name]_D - Base Color
T_[Texture Name]_R - Roughness
T_[Texture Name]_S - Specular
T_[Texture Name]_N - Normal
T_[Texture Name]_M - Metalic
T_[Texture Name]_AO - Ambient Occlusion
T_[Texture Name]_H - Height
T_[Texture Name]_MSK - Mask
T_[Texture Name]_F - Flow Map
