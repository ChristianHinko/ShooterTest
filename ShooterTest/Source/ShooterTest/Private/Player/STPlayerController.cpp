// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/STPlayerController.h"



ASTPlayerController::ASTPlayerController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}


void ASTPlayerController::InitPlayerState()
{
    Super::InitPlayerState();
    // Right after Player State gets created
}
void ASTPlayerController::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();
    // Right after Player State gets repped
}

void ASTPlayerController::EndPlayingState()
{
    Super::EndPlayingState();

    //if (ASTCharacter* STCharacter = Cast<ASTCharacter>(GetPawn()))
    //{
    //    STCharacter->SetRemoteViewYaw(0.f);
    //}
}
