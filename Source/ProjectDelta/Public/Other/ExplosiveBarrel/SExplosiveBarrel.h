// Project Delta Copyright Inc. All rights are reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SExplosiveBarrel.generated.h"

UCLASS()
class PROJECTDELTA_API ASExplosiveBarrel : public AActor
{
    GENERATED_BODY()

public:
    ASExplosiveBarrel();
    
    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

    //Components of actor
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent *MeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    class URadialForceComponent *ForceComponent;


public:
    UFUNCTION()
    void HitMesh(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                 FVector NormalImpulse, const FHitResult &Hit);
};
