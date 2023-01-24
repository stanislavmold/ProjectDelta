// Project Delta Copyright Inc. All rights are reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SGameInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USGameInterface : public UInterface
{
    GENERATED_BODY()
};



class PROJECTDELTA_API ISGameInterface
{
    GENERATED_BODY()

public:
    
    UFUNCTION(BlueprintNativeEvent)
    void Interact(APawn *InstigatorPawn);
};
