// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CHCharacterBase.h"
#include "InputActionValue.h"
#include "Interface/CHWeaponInterface.h"
#include "Components/TimelineComponent.h"
#include "CHCharacterPlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerAttackTrigger);

/**
 * 
 */
UCLASS()
class SPARTA_CH3_5_SDI_API ACHCharacterPlayer : public ACHCharacterBase, public ICHWeaponInterface
{
	GENERATED_BODY()
	
public:
	ACHCharacterPlayer();
	
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	
	
	// Camera Section
public:
	FVector GetFPSCameraLocation() const;
	FVector GetFPSCameraForwardDirection() const;
protected:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera)
	TObjectPtr<class UCameraComponent> FPSCamera;
	
	float DefaultFOV;
	float TargetFOV;
	
	UPROPERTY(EditAnywhere, Category = "Camera|FOV")
	TObjectPtr<UCurveFloat> FOVCurve;
	
private:
	FTimeline FOVTimeline;
	
	UFUNCTION()
	void HandleTimelineProgress(float Value);
	
	// Movement Section
public:
	FPlayerAttackTrigger OnPlayerAttackTrigger;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> DefaultIMC;	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	TObjectPtr<class UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	TObjectPtr<class UInputAction> LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	TObjectPtr<class UInputAction> JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	TObjectPtr<class UInputAction> AttackAction;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	
	// Equipment Section
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Equipment)
	TObjectPtr<class UCHEquipmentComponent> EquipmentComp;
	
	// Weapon Section
public:
	virtual FHitResult PerformLineTraceForProjectileWeapon() override;
	
	void RecoilCameraByWeaponFire();
};
