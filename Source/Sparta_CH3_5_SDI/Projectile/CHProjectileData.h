// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CHProjectileData.generated.h"

/**
 * 
 */
UCLASS()
class SPARTA_CH3_5_SDI_API UCHProjectileData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UCHProjectileData();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ProjectileData")
	TObjectPtr<class UStaticMesh> Mesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ProjectileData")
	float Speed;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ProjectileData")
	float Damage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ProjectileData")
	FVector Scale;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ProjectileData")
	FVector Offset;
};
