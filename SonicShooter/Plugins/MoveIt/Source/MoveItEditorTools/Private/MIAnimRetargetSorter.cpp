// Copyright (c) 2019-2021 Drowning Dragons Limited. All Rights Reserved.


#include "MIAnimRetargetSorter.h"
#include "EditorUtilityLibrary.h"
#include "Interfaces/IPluginManager.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "AssetRegistryModule.h"
#include "AssetToolsModule.h"

DEFINE_LOG_CATEGORY_STATIC(LogRetargeter, Log, All);

TArray<FString> UMIAnimRetargetSorter::GetSelectedDirectories()
{
	TArray<FString> Folders;
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	IContentBrowserSingleton& ContentBrowserSingleton = ContentBrowserModule.Get();
	ContentBrowserSingleton.GetSelectedPathViewFolders(Folders);
	return Folders;
}

void UMIAnimRetargetSorter::ArrangeRetargetedAnimations(const FString& Path, TArray<UObject *> SelectedObjects, const FString& Prefix, const FString& Suffix, const FString& Replace, const FString& ReplaceWith)
{
	if (SelectedObjects.Num() == 0)
	{
		return;
	}

	FString Content = IPluginManager::Get().FindPlugin(TEXT("MoveIt"))->GetContentDir();
	FString SourcePath = Content + Path;
	const FString MoveItPath = "/MoveIt" +Path;

	if (!FPaths::DirectoryExists(SourcePath))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(697978, 10.f, FColor::Red, FString::Printf(TEXT("Path {  %s  } does not exist"), *SourcePath));
		}
		UE_LOG(LogRetargeter, Error, TEXT("Path {  %s  } does not exist"), *SourcePath);
		return;
	}

	FAssetToolsModule& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> MIAssetData;
	AssetRegistryModule.Get().GetAssetsByPath(*MoveItPath, MIAssetData, true);

	// MoveIt Anim, Retargeted Anim
	TMap<FAssetData, FAssetData> AssetDataMap;

	// Get matching asset data
	for (const UObject* Obj : SelectedObjects)
	{
		for (FAssetData& AD : MIAssetData)
		{
			FString OrigName = Obj->GetName();
			// Replace string
			if (!Replace.IsEmpty() || !ReplaceWith.IsEmpty())
			{
				OrigName = Obj->GetName().Replace(*ReplaceWith, *Replace);
			}
			// Remove Prefix
			if (!Prefix.IsEmpty())
			{
				OrigName.RemoveFromStart(Prefix);
			}
			// Remove Suffix
			if (!Suffix.IsEmpty())
			{
				OrigName.RemoveFromEnd(Suffix);
			}

			// Now left with original name (as MoveIt has it)
			const FName OrigAssetName = *OrigName;
			if (AD.AssetName.IsEqual(OrigAssetName))
			{
				FAssetData RetargetAD = AssetRegistryModule.Get().GetAssetByObjectPath(*Obj->GetPathName());
				AssetDataMap.Add(AD, RetargetAD);
				break;
			}
		}
	}

	TArray<FAssetRenameData> RenameData;

	// Move retargeted animations
	for (auto& AD : AssetDataMap)
	{
		FAssetData& MIData = AD.Key;
		FAssetData& TData = AD.Value;

		// Remove Class from Package Path
		FString OldPackagePath = MIData.PackagePath.ToString();
		FString NewPackagePath = TData.PackagePath.ToString();

		FString PackagePath = OldPackagePath.Replace(TEXT("/MoveIt"), TEXT(""), ESearchCase::CaseSensitive);
		PackagePath = NewPackagePath + PackagePath;
		FString PackageName = TData.GetAsset()->GetName() + "." + TData.GetAsset()->GetName();

		FAssetRenameData Rename;
		Rename.Asset = TData.GetAsset();
		Rename.NewPackagePath = PackagePath;
		Rename.NewName = TData.AssetName.ToString();

		RenameData.Add(Rename);
	}

	AssetTools.Get().RenameAssets(RenameData);
}
