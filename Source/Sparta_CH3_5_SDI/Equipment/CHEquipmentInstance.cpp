// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/CHEquipmentInstance.h"
#include "Equipment/CHEquipmentDefinition.h"
#include "Character/CHCharacterPlayer.h"
#include "Projectile/CHProjectileBase.h"
#include "Interface/CHWeaponInterface.h"

// Sets default values
ACHEquipmentInstance::ACHEquipmentInstance()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
}

void ACHEquipmentInstance::SetCHEquipmentDefinition(UCHEquipmentDefinition* InDefinition)
{
	EquipmentDefinition = InDefinition;
	StaticMesh->SetStaticMesh(EquipmentDefinition->Mesh);
}
