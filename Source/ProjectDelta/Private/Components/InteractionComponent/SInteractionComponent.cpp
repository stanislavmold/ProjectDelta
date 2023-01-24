// Project Delta Copyright Inc. All rights are reserved


#include "Components/InteractionComponent/SInteractionComponent.h"

#include "DrawDebugHelpers.h"
#include "VectorUtil.h"
#include "Character/SCharacter.h"
#include "Interface/SGameInterface.h"
#include "Engine/World.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}


void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void USInteractionComponent::BeginPlay()
{
    Super::BeginPlay();
}

void USInteractionComponent::PrimaryInteract()
{
    if (!GetWorld()) return;

    FCollisionObjectQueryParams ObjectQueryParams;
    ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

    AActor *Owner = GetOwner();

    FVector EyeLocation;
    FRotator EyeRotation;
    Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

    constexpr float LengthTrace = 1000.f;

    FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * LengthTrace);

    /*FHitResult HitResult;
    bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(HitResult, EyeLocation, TraceEnd, ObjectQueryParams);*/

    FCollisionShape Shape;
    Shape.SetSphere(30.f);

    TArray<FHitResult> Hits;
    bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, TraceEnd, FQuat::Identity,
                                                           ObjectQueryParams, Shape);

    FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

    for (FHitResult Hit : Hits)
    {
        if (AActor *HitActor = Hit.GetActor())
        {
            if (HitActor->Implements<USGameInterface>())
            {
                auto *Pawn = Cast<APawn>(Owner);

                ISGameInterface::Execute_Interact(HitActor, Pawn);
            }
            //debug only
            DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 32.f, 5, LineColor);
        }
    }

    //debug only
    DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, LineColor, false, 2.f, 0.f, 2.5f);
}
