// Copyright 2017-2020 Puny Human, All Rights Reserved.


#include "Data/ArcTeamDefinition.h"

UArcTeamDefinition::UArcTeamDefinition(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bAutoJoinable = true;
}

FPrimaryAssetId UArcTeamDefinition::GetPrimaryAssetId() const
{
	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		UClass* SearchNativeClass = GetClass();

		while (SearchNativeClass && !SearchNativeClass->HasAnyClassFlags(CLASS_Native | CLASS_Intrinsic))
		{
			SearchNativeClass = SearchNativeClass->GetSuperClass();
		}

		if (SearchNativeClass && SearchNativeClass != GetClass())
		{
			// If blueprint, return native class and asset name
			return FPrimaryAssetId(TEXT("ArcTeamDefinition"), FPackageName::GetShortFName(GetOutermost()->GetFName()));
		}

		// Native CDO, return nothing
		return FPrimaryAssetId();
	}

	return  GetClass()->GetDefaultObject()->GetPrimaryAssetId();
}

UArcTeamDefinition_Spectator::UArcTeamDefinition_Spectator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bAutoJoinable = false;
}

UArcTeamUIObject_TeamDefinition::UArcTeamUIObject_TeamDefinition(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}
