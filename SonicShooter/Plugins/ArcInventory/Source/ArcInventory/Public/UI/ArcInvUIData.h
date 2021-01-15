// 2017-2018 Puny Human Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ArcInvUIData.generated.h"

/** Base Class for UI Data objects. 
 *  This is intended to be implemented in blueprint and used as needed for UI data 
 *  This object is never loaded on a dedicated server
 */
UCLASS(Blueprintable, BlueprintType, EditInlineNew, Abstract)
class ARCINVENTORY_API UArcInvUIData : public UObject
{
	GENERATED_BODY()
public:
	UArcInvUIData();
};
