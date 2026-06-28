// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/CHEquipmentDefinition.h"
#include "CHWeaponDefinition.generated.h"

/**
 * 
 */
UCLASS()
class SPARTA_CH3_5_SDI_API UCHWeaponDefinition : public UCHEquipmentDefinition
{
	GENERATED_BODY()
	
public:
	UCHWeaponDefinition();
	
	UPROPERTY(Editdefaultsonly, BlueprintReadWrite, Category = Weapon)
	TSubclassOf<class ACHProjectileBase> ProjectileClass;

};
