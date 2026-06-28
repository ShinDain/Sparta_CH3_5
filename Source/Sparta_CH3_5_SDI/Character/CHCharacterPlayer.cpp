// Fill out your copyright notice in the Description page of Project Settings.


#include "CHCharacterPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "Equipment/CHEquipmentComponent.h"
#include "Equipment/CHWeaponDefinition.h"
#include "Equipment/CHWeaponInstance.h"
#include "Physics/CHCollision.h"

ACHCharacterPlayer::ACHCharacterPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	
	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FOVCamera"));
	FPSCamera->SetupAttachment(RootComponent);
	
	EquipmentComp = CreateDefaultSubobject<UCHEquipmentComponent>(TEXT("EquipmentComponent"));
}

void ACHCharacterPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (FOVTimeline.IsPlaying())
	{
		FOVTimeline.TickTimeline(DeltaSeconds);
	}
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

void ACHCharacterPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	OnPlayerAttackTrigger.AddDynamic(EquipmentComp, &UCHEquipmentComponent::OnAttack);
	
	if (FPSCamera)
	{
		DefaultFOV = FPSCamera->FieldOfView;
	}
	if (FOVCurve)
	{
		FOnTimelineFloat ProgressFunction;
		ProgressFunction.BindUFunction(this, FName("HandleTimelineProgress"));
		
		FOVTimeline.AddInterpFloat(FOVCurve, ProgressFunction);
		//FOVTimeline.SetTimelineLength(1.0f);
		FOVTimeline.SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);
	}
	if (EquipmentComp)
	{
		EquipmentComp->OnWeaponAttackSuccessed.AddUObject(this, &ACHCharacterPlayer::RecoilCameraByWeaponFire);
	}
}

FVector ACHCharacterPlayer::GetFPSCameraLocation() const
{
	return FPSCamera->GetComponentLocation();
}

FVector ACHCharacterPlayer::GetFPSCameraForwardDirection() const
{
	return FPSCamera->GetForwardVector();
}

void ACHCharacterPlayer::HandleTimelineProgress(float Value)
{
	if (FPSCamera)
	{
		float NewFOV = FMath::Lerp(DefaultFOV, TargetFOV, Value);
		FPSCamera->SetFieldOfView(NewFOV);
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

void ACHCharacterPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	AddControllerYawInput(LookAxisVector.X);	
	
	const FRotator CameraRotation = FPSCamera->GetRelativeRotation();
	FRotator NewCameraRotation(CameraRotation.Pitch, CameraRotation.Yaw, 0.0f);
	NewCameraRotation.Pitch = FMath::Clamp(NewCameraRotation.Pitch + LookAxisVector.Y, -89.0f, 89.0f);
	FPSCamera->SetRelativeRotation(NewCameraRotation);
}

void ACHCharacterPlayer::Attack(const FInputActionValue& Value)
{
	OnPlayerAttackTrigger.Broadcast();
}

FHitResult ACHCharacterPlayer::PerformLineTraceForProjectileWeapon()
{
	UWorld* World = GetWorld();
	if (World == nullptr)
		return FHitResult();
	
	FVector StartLocation = GetFPSCameraLocation();
	FVector EndLocation = GetFPSCameraLocation() + (GetFPSCameraForwardDirection() * 5000.0f);
	
	FHitResult HitResult;
	
	FCollisionQueryParams QueryParams;
	TArray<AActor*> IgnoredActors = {this, GetOwner()};
	QueryParams.AddIgnoredActors(IgnoredActors);
	QueryParams.bTraceComplex = false;
	
	ECollisionChannel TraceChannel = CCHANNEL_CHPROJECTILE;
	bool bHit = World->LineTraceSingleByChannel(
		HitResult, StartLocation, EndLocation, TraceChannel,
		QueryParams
		);
	
	DrawDebugLine(World, StartLocation, EndLocation, FColor::Red, false, 3.0f);
		
	if (bHit)
	{
		DrawDebugSphere(World, HitResult.ImpactPoint, 5.0, 16, FColor::Green, false, 5.0f);
		
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			UE_LOG(LogTemp, Log, TEXT("Hit Actor is %s"), *HitActor->GetName());
		}
	}
	
	return HitResult;
}

void ACHCharacterPlayer::RecoilCameraByWeaponFire()
{
	UE_LOG(LogTemp, Log, TEXT("RecoilFunction Called"));
	
	if (FOVCurve
		&& EquipmentComp)
	{
		const UCHWeaponDefinition* Definition = EquipmentComp->GetWeaponDefinition();
		float RecoilFOVOffset = 3.0f;
		if (Definition)
			RecoilFOVOffset = Definition->RecoilFOVOffset;
		
		TargetFOV = DefaultFOV - RecoilFOVOffset;
		
		FOVTimeline.PlayFromStart();
	}
}
