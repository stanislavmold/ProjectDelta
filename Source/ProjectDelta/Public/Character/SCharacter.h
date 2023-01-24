// Project Delta Copyright Inc. All rights are reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

UCLASS()
class PROJECTDELTA_API ASCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASCharacter();

public:
    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;


    //Components and classes for our character
protected:
    UPROPERTY(VisibleAnywhere, Category = "CameraComponent")
    class UCameraComponent *CameraComponent;

    UPROPERTY(VisibleAnywhere, Category = "CameraComponent")
    class USpringArmComponent *SpringArmComponent;

    UPROPERTY(EditAnywhere)
    TSubclassOf<AActor> ProjectileClass;

    UPROPERTY(VisibleAnywhere)
    class USInteractionComponent *InteractionComponent;

    //Movement functions
public:
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

    void MoveForward(float Value);
    void MoveRight(float Value);
    void LookUp(float Value);
    void TurnAround(float Value);

    //Pressed key functions
protected:
    void PrimaryAttack();
    void Interact();
};
