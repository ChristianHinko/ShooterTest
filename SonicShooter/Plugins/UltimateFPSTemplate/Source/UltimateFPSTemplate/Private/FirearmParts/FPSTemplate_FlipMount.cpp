// Copyright 2021, Dakota Dawe, All rights reserved


#include "FirearmParts/FPSTemplate_FlipMount.h"

#include "FPSTemplate_PartComponent.h"
#include "Net/UnrealNetwork.h"

AFPSTemplate_FlipMount::AFPSTemplate_FlipMount()
{
	bIsFolded = true;
	PartType = EPartType::FlipMount;
}

void AFPSTemplate_FlipMount::OnRep_IsFolded()
{
	if (bIsFolded)
	{
		if (FoldedAnimation)
		{
			PartMesh->PlayAnimation(FoldedAnimation, false);
		}
	}
	else if (OpenAnimation)
	{
		PartMesh->PlayAnimation(OpenAnimation, false);
	}
}

void AFPSTemplate_FlipMount::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFPSTemplate_FlipMount, bIsFolded);
}

bool AFPSTemplate_FlipMount::Server_SetFolded_Validate(bool Folded)
{
	return true;
}

void AFPSTemplate_FlipMount::Server_SetFolded_Implementation(bool Folded)
{
	bIsFolded = Folded;
	OnRep_IsFolded();
}

void AFPSTemplate_FlipMount::Use_Implementation()
{
	bIsFolded = !bIsFolded;
	if (!HasAuthority())
	{
		Server_SetFolded(bIsFolded);
	}
	//DisableRenderTarget(!bIsFolded);
	OnRep_IsFolded();

	Super::Use_Implementation();
}

void AFPSTemplate_FlipMount::DisableRenderTarget(bool Disable)
{
	if (bIsFolded)
	{
		return;
	}
	for (UFPSTemplate_PartComponent* PartComponent : PartComponents)
	{
		if (PartComponent && PartComponent->GetPart() && PartComponent->GetPart()->HasRenderTarget())
		{
			PartComponent->GetPart()->DisableRenderTarget(Disable);
		}
	}
}
