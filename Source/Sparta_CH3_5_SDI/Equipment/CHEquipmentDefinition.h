// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CHEquipmentDefinition.generated.h"

UENUM()
enum class ECHEquipmentSlot
{
	Weapon,
	End,
};

/**
 * 
 */
UCLASS()
class SPARTA_CH3_5_SDI_API UCHEquipmentDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	TObjectPtr<class UStaticMesh> Mesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	ECHEquipmentSlot Slot;
};
