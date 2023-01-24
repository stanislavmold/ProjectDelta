// Project Delta Copyright Inc. All rights are reserved


#include "Other/ExplosiveBarrel/SExplosiveBarrel.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

ASExplosiveBarrel::ASExplosiveBarrel()
{
    PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
    RootComponent = MeshComponent;

    ForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
    ForceComponent->ImpulseStrength = 1000.f;
    ForceComponent->Radius = 2000.f;
    ForceComponent->SetupAttachment(MeshComponent);
}

void ASExplosiveBarrel::BeginPlay()
{
    Super::BeginPlay();

    MeshComponent->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::HitMesh);
}


void ASExplosiveBarrel::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASExplosiveBarrel::HitMesh(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                                FVector NormalImpulse, const FHitResult &Hit)
{
    ForceComponent->FireImpulse();
}
