// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ArcTeamInterface_Gamemode.generated.h"

class AController;
class UArcTeamComponent_Gamemode; 

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UArcTeamInterface_Gamemode : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARCTEAMS_API IArcTeamInterface_Gamemode
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual UArcTeamComponent_Gamemode* GetTeamComponent() const = 0;

	virtual AActor* ChooseTeamPlayerStart(AController* Player);

};
