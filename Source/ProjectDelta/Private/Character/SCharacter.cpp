// Project Delta Copyright Inc. All rights are reserved


#include "Character/SCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
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

    //Debug for movement

    // -- Rotation Visualization -- //
    const float DrawScale = 100.0f;
    const float Thickness = 5.0f;

    FVector LineStart = GetActorLocation();
    // Offset to the right of pawn
    LineStart += GetActorRightVector() * 100.0f;
    // Set line end in direction of the actor's forward
    FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
    // Draw Actor's Direction
    DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0,
                              Thickness);

    FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
    // Draw 'Controller' Rotation ('PlayerController' that 'possessed' this character)
    DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f,
                              0, Thickness);
}


void ASCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ThisClass::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ThisClass::LookUp);
    PlayerInputComponent->BindAxis("TurnAround", this, &ThisClass::TurnAround);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ThisClass::Jump);

    PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ThisClass::PrimaryAttack);
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

void ASCharacter::PrimaryAttack()
{
    const FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

    const FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    if (!ProjectileClass) return;

    GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}
