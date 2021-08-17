// Copyright (c) 2019-2021 Drowning Dragons Limited. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blutility/Classes/EditorUtilityWidget.h"
#include "MIAnimRetargetSorter.generated.h"

/**
 * 
 */
UCLASS()
class MOVEITEDITORTOOLS_API UMIAnimRetargetSorter : public UEditorUtilityWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Development|Editor")
	TArray<FString> GetSelectedDirectories();

	UFUNCTION(BlueprintCallable, Category = "Development|Editor")
	void ArrangeRetargetedAnimations(const FString& Path, TArray<UObject*> SelectedObjects, const FString& Prefix, const FString& Suffix, const FString& Replace, const FString& ReplaceWith);
};
