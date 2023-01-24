// Project Delta Copyright Inc. All rights are reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/SGameInterface.h"
#include "SItemChest.generated.h"

UCLASS()
class PROJECTDELTA_API ASItemChest : public AActor, public ISGameInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    float PitchValue;

    virtual void Interact_Implementation(APawn *InstigatorPawn) override;

public:
    ASItemChest();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent *BaseMesh;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent *LidMesh;
};
