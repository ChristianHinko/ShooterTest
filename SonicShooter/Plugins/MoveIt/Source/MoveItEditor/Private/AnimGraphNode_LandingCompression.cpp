// Copyright (c) 2019-2021 Drowning Dragons Limited. All Rights Reserved.


#include "AnimGraphNode_LandingCompression.h"
#include "PropertyHandle.h"
#include "DetailLayoutBuilder.h"


#define LOCTEXT_NAMESPACE "A3Nodes"


FText UAnimGraphNode_LandingCompression::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if ((TitleType == ENodeTitleType::ListView || TitleType == ENodeTitleType::MenuTitle) && (Node.SpringBone.BoneName == NAME_None))
	{
		return GetControllerDescription();
	}
	// @TODO: the bone can be altered in the property editor, so we have to 
	//        choose to mark this dirty when that happens for this to properly work
	else //if(!CachedNodeTitles.IsTitleCached(TitleType, this))
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("ControllerDescription"), GetControllerDescription());
		Args.Add(TEXT("BoneName"), FText::FromName(Node.SpringBone.BoneName));

		// FText::Format() is slow, so we cache this to save on performance
		if (TitleType == ENodeTitleType::ListView || TitleType == ENodeTitleType::MenuTitle)
		{
			CachedNodeTitles.SetCachedTitle(TitleType, FText::Format(LOCTEXT("AnimGraphNode_SpringBone_ListTitle", "{ControllerDescription} - Bone: {BoneName}"), Args), this);
		}
		else
		{
			CachedNodeTitles.SetCachedTitle(TitleType, FText::Format(LOCTEXT("AnimGraphNode_SpringBone_Title", "{ControllerDescription}\nBone: {BoneName}"), Args), this);
		}
	}

	return CachedNodeTitles[TitleType];
}

FText UAnimGraphNode_LandingCompression::GetControllerDescription() const
{
	return LOCTEXT("LandingCompressionName", "Landing Compression");
}

FText UAnimGraphNode_LandingCompression::GetTooltipText() const
{
	return LOCTEXT("AnimGraphNode_LandingCompression_Tooltip", "Applies physics spring to compress the character using impact velocity when landing.");
}

FString UAnimGraphNode_LandingCompression::GetNodeCategory() const
{
	return TEXT("MoveIt!");
}

void UAnimGraphNode_LandingCompression::CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const
{
	Super::CustomizePinData(Pin, SourcePropertyName, ArrayIndex);

	const FAnimNode_LandingCompression* LookNode = &Node;

	if (Pin->PinName == GET_MEMBER_NAME_STRING_CHECKED(FAnimNode_LandingCompression, Velocity))
	{
		Pin->bHidden = true;
	}

	if (Pin->PinName == GET_MEMBER_NAME_STRING_CHECKED(FAnimNode_LandingCompression, bAlphaBoolEnabled))
	{
		Pin->bHidden = true;
	}
}

void UAnimGraphNode_LandingCompression::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	Super::CustomizeDetails(DetailBuilder);

	const FAnimNode_LandingCompression* LookNode = &Node;

	TSharedRef<IPropertyHandle> NodeHandle = DetailBuilder.GetProperty(FName(TEXT("Node")), GetClass());

	DetailBuilder.HideProperty(NodeHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FAnimNode_LandingCompression, Velocity)));
	DetailBuilder.HideProperty(NodeHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FAnimNode_LandingCompression, bSimulateInComponentSpace)));
	DetailBuilder.HideProperty(NodeHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FAnimNode_LandingCompression, AlphaInputType)));
	DetailBuilder.HideProperty(NodeHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FAnimNode_LandingCompression, bAlphaBoolEnabled)));
}

#undef LOCTEXT_NAMESPACE
