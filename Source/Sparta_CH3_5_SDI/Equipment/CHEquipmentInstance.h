// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CHEquipmentInstance.generated.h"

UCLASS()
class SPARTA_CH3_5_SDI_API ACHEquipmentInstance : public AActor
{
	GENERATED_BODY()
	
public:
	ACHEquipmentInstance();
	
	virtual void SetCHEquipmentDefinition(class UCHEquipmentDefinition* InDefinition);
	
	// Weapon Section
public:
	UFUNCTION()
	virtual void OnAttack();
protected:
	void FireProjectileWeapon(); 
	
protected:
	TObjectPtr<UCHEquipmentDefinition> EquipmentDefinition;
	TSubclassOf<class ACHProjectileBase> ProjectileClass;
	TObjectPtr<class UStaticMeshComponent> StaticMesh;

};
