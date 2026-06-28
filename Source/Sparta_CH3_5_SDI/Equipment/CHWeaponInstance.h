// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/CHEquipmentInstance.h"
#include "CHWeaponInstance.generated.h"

class UCHEquipmentDefinition;
class UCHWeaponDefinition;

DECLARE_MULTICAST_DELEGATE(FOnFireSuccess);
/**
 * 
 */
UCLASS()
class SPARTA_CH3_5_SDI_API ACHWeaponInstance : public ACHEquipmentInstance
{
	GENERATED_BODY()
		
public:
	ACHWeaponInstance();
	virtual void SetCHEquipmentDefinition(UCHEquipmentDefinition* InDefinition) override;
	
public:
	virtual void OnActive() override;
	const UCHWeaponDefinition* GetWeaponDefinition() const;
	
	void RegisterOnFireSuccess(FSimpleDelegate InDelegate);
	
protected:
	FOnFireSuccess OnFireSuccess;
	void FireProjectileWeapon();
	
protected:
	UPROPERTY()
	TObjectPtr<UCHWeaponDefinition> WeaponDefinition;
	
	TSubclassOf<class ACHProjectileBase> ProjectileClass;
};
