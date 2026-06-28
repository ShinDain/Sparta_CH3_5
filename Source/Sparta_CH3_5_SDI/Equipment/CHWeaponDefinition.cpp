// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/CHWeaponDefinition.h"

UCHWeaponDefinition::UCHWeaponDefinition()
	:Super()
{
	Slot = ECHEquipmentSlot::Weapon;
	RecoilFOVOffset = 5.0f;
	//FOVRecoverySpeed = 10.0f;
}
