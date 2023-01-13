// Project Delta Copyright Inc. All rights are reserved


#include "Character/SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


ASCharacter::ASCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SetupAttachment(RootComponent);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    GetCharacterMovement()->bOrientRotationToMovement = true;

    bUseControllerRotationYaw = false;
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
    //the character is going to move in the direction of our camera;
    FRotator ControlRotation = GetControlRotation();
    ControlRotation.Pitch = 0.f;
    ControlRotation.Roll = 0.f;

    AddMovementInput(ControlRotation.Vector(), Value);
}

void ASCharacter::MoveRight(float Value)
{
    //this code is fixing weird movement at Y axis;
    FRotator ControlRotation = GetControlRotation();
    ControlRotation.Pitch = 0.f;
    ControlRotation.Roll = 0.f;

    const FVector RightVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);

    AddMovementInput(RightVector, Value);
}

void ASCharacter::LookUp(float Value)
{
    AddControllerYawInput(Value);
}

void ASCharacter::TurnAround(float Value)
{
    AddControllerPitchInput(Value);
}
