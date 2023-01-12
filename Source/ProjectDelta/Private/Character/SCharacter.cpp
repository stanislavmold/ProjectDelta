// Project Delta Copyright Inc. All rights are reserved


#include "Character/SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


ASCharacter::ASCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(RootComponent);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
}


void ASCharacter::BeginPlay()
{
    Super::BeginPlay();
}


void ASCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


void ASCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ThisClass::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ThisClass::LookUp);
    PlayerInputComponent->BindAxis("TurnAround", this, &ThisClass::TurnAround);
}

void ASCharacter::MoveForward(float Value)
{
    AddMovementInput(GetActorForwardVector(), Value);
}

void ASCharacter::MoveRight(float Value)
{
    AddMovementInput(GetActorRightVector(), Value);
}

void ASCharacter::LookUp(float Value)
{
    AddControllerYawInput(Value);
}

void ASCharacter::TurnAround(float Value)
{
    AddControllerPitchInput(Value);
}
