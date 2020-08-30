// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SSAbilitySystemBlueprintLibrary.h"

#include "AbilitySystem/TargetActors/GATDF_MultiFilter.h"



FGATDF_MultiFilterHandle USSAbilitySystemBlueprintLibrary::MakeMultiFilterHandle(FGATDF_MultiFilter MultiFilter, AActor* FilterActor)
{
	FGATDF_MultiFilterHandle FilterHandle;
	FGATDF_MultiFilter* NewFilter = new FGATDF_MultiFilter(MultiFilter);
	//NewFilter->InitializeFilterContext(FilterActor);
	FilterHandle.MultiFilter = TSharedPtr<FGATDF_MultiFilter>(NewFilter);
	return FilterHandle;
}
