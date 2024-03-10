// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "InputConfigData.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create a camera boom
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f;
    CameraBoom->bUsePawnControlRotation = true;
    // Create a follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;
}

void AMainCharacter::MoveForward(const FInputActionValue& Value)
{
    if (Controller != nullptr)
    {
        const FVector2D MoveValue = Value.Get<FVector2D>();
        const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

        // Forward/Backward direction
        if (MoveValue.Y != 0.f)
        {
            // Get forward vector
            const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);

            AddMovementInput(Direction, MoveValue.Y);
        }
    }
}

void AMainCharacter::MoveBackward(const FInputActionValue& Value)
{
    if (Controller != nullptr)
    {
        const FVector2D MoveValue = Value.Get<FVector2D>();
        const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

        // Forward/Backward direction
        if (MoveValue.Y != 0.f)
        {
            // Get forward vector
            const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);

            AddMovementInput(Direction, MoveValue.Y);
        }
    }
}

void AMainCharacter::MoveRight(const FInputActionValue& Value)
{
    if (Controller != nullptr)
    {
        const FVector2D MoveValue = Value.Get<FVector2D>();
        const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

        // Right/Left direction
        if (MoveValue.X != 0.f)
        {
            // Get right vector
            const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);

            AddMovementInput(Direction, MoveValue.X);
        }
    }
}

void AMainCharacter::MoveLeft(const FInputActionValue& Value)
{
    if (Controller != nullptr)
    {
        const FVector2D MoveValue = Value.Get<FVector2D>();
        const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

        // Right/Left direction
        if (MoveValue.X != 0.f)
        {
            // Get right vector
            const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);

            AddMovementInput(Direction, MoveValue.X);
        }
    }
}

void AMainCharacter::Look(const FInputActionValue& Value)
{
    FVector2D InputValue = Value.Get<FVector2D>();
    if (Controller != nullptr)
    {
        if (InputValue.X != 0.0f)
        {
            AddControllerYawInput(InputValue.X);
        }
        if (InputValue.Y != 0.0f)
        {
            AddControllerPitchInput(-InputValue.Y);
        }

    }
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // Get the player controller
    APlayerController* PC = Cast<APlayerController>(GetController());

    // Get the local player subsystem
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
    // Clear out existing mapping, and add our mapping
    Subsystem->ClearAllMappings();
    Subsystem->AddMappingContext(InputMapping, 0);

    // Get the EnhancedInputComponent
    UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    // Move
    PEI->BindAction(InputActions->InputForward, ETriggerEvent::Triggered, this, &AMainCharacter::MoveForward);
    PEI->BindAction(InputActions->InputBackward, ETriggerEvent::Triggered, this, &AMainCharacter::MoveBackward);
    PEI->BindAction(InputActions->InputRight, ETriggerEvent::Triggered, this, &AMainCharacter::MoveRight);
    PEI->BindAction(InputActions->InputLeft, ETriggerEvent::Triggered, this, &AMainCharacter::MoveLeft);
    // Look
    PEI->BindAction(InputActions->InputLook, ETriggerEvent::Triggered, this, &AMainCharacter::Look);

}

