// Copyright 2017-2020 Puny Human, All Rights Reserved.

 
#include "Perks/ArcItemPerkTypes.h"


FArchive& operator<<(FArchive& Ar, FArcPerkModifierData& PerkMod)
{
	FProperty* Prop = nullptr;

	if (Ar.IsSaving())
	{
		Prop = PerkMod.Attribute.GetUProperty();
	}

	Ar << Prop;

	if (Ar.IsLoading())
	{
		PerkMod.Attribute = FGameplayAttribute(Prop);
	}

	Ar << PerkMod.ModifierOp;
	Ar << PerkMod.Value;

	return Ar;
}