// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/CHEquipmentInstance.h"
#include "CHWeaponInstance.generated.h"

/**
 * 
 */
UCLASS()
class SPARTA_CH3_5_SDI_API ACHWeaponInstance : public ACHEquipmentInstance
{
	GENERATED_BODY()
		
public:
	ACHWeaponInstance();
	virtual void SetCHEquipmentDefinition(class UCHEquipmentDefinition* InDefinition) override;
	
public:
	virtual void OnActive() override;
	
protected:
	void FireProjectileWeapon();
	
protected:
	TObjectPtr<class UCHWeaponDefinition> WeaponDefinition;
	TSubclassOf<class ACHProjectileBase> ProjectileClass;
};
