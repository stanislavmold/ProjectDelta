// Project Delta Copyright Inc. All rights are reserved


#include "ItemChest/SItemChest.h"


// Sets default values
ASItemChest::ASItemChest()
{
    PrimaryActorTick.bCanEverTick = true;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMeshComponent");
    RootComponent = BaseMesh;

    LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMeshComponent");
    LidMesh->SetupAttachment(RootComponent);

    PitchValue = 100.f;
}

void ASItemChest::BeginPlay()
{
    Super::BeginPlay();
}

void ASItemChest::Interact_Implementation(APawn *InstigatorPawn)
{
    ISGameInterface::Interact_Implementation(InstigatorPawn);

    LidMesh->SetRelativeRotation(FRotator(PitchValue));  
}
