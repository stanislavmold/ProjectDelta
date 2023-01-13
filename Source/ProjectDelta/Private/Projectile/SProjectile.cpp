// Project Delta Copyright Inc. All rights are reserved


#include "Projectile/SProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

ASProjectile::ASProjectile()
{
    PrimaryActorTick.bCanEverTick = true;

    SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    SphereComponent->SetCollisionProfileName("Projectile");
    RootComponent = SphereComponent;

    ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystem");
    ParticleSystemComponent->SetupAttachment(RootComponent);

    ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
    ProjectileMovementComp->InitialSpeed = 1200.f;
    ProjectileMovementComp->bRotationFollowsVelocity = true;
    ProjectileMovementComp->bInitialVelocityInLocalSpace = true;
}

void ASProjectile::BeginPlay()
{
    Super::BeginPlay();
}

void ASProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
