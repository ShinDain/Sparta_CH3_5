// Fill out your copyright notice in the Description page of Project Settings.


#include "CHCharacterPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"

ACHCharacterPlayer::ACHCharacterPlayer()
{
	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FOVCamera"));
	FPSCamera->SetupAttachment(RootComponent);
}

void ACHCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACHCharacterPlayer::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACHCharacterPlayer::Look);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ACHCharacterPlayer::Attack);
	
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		InputSubsystem->ClearAllMappings();
		if (DefaultIMC)
		{
			InputSubsystem->AddMappingContext(DefaultIMC, 0);
		}
	}
}

void ACHCharacterPlayer::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw,0);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
}

PRAGMA_DISABLE_OPTIMIZATION
void ACHCharacterPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	AddControllerYawInput(LookAxisVector.X);	
	
	const FRotator CameraRotation = FPSCamera->GetRelativeRotation();
	FRotator NewCameraRotation(CameraRotation.Pitch, CameraRotation.Yaw, 0.0f);
	NewCameraRotation.Pitch = FMath::Clamp(NewCameraRotation.Pitch + LookAxisVector.Y, -89.0f, 89.0f);
	FPSCamera->SetRelativeRotation(NewCameraRotation);
}
PRAGMA_ENABLE_OPTIMIZATION

void ACHCharacterPlayer::Attack(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Log, TEXT("Attacked"));
}
