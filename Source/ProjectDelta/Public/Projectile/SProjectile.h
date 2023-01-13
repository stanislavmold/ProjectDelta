// Project Delta Copyright Inc. All rights are reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UParticleSystemComponent;

UCLASS()
class PROJECTDELTA_API ASProjectile : public AActor
{
    GENERATED_BODY()

public:
    ASProjectile();

public:
    virtual void Tick(float DeltaTime) override;
    
protected:
    virtual void BeginPlay() override;

//Components of actor
protected:
    UPROPERTY(VisibleAnywhere)
    UProjectileMovementComponent* ProjectileMovementComp;

    UPROPERTY(VisibleAnywhere)
    USphereComponent* SphereComponent;

    UPROPERTY(VisibleAnywhere)
    UParticleSystemComponent* ParticleSystemComponent;
};
