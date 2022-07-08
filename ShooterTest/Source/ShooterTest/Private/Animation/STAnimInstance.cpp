// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/STAnimInstance.h"



USTAnimInstance::USTAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	if (IAnimClassInterface* AnimBlueprintClass = IAnimClassInterface::GetFromClass(GetClass()))
	{
		if (UAnimBlueprint* Blueprint = Cast<UAnimBlueprint>(Cast<UAnimBlueprintGeneratedClass>(AnimBlueprintClass)->ClassGeneratedBy))
		{
			Blueprint->bWarnAboutBlueprintUsage = true;
		}
	}
#endif


}
