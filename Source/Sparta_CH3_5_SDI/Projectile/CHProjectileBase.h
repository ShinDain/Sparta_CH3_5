// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CHProjectileBase.generated.h"

USTRUCT(BlueprintType)
struct FProjectileData
{
	GENERATED_BODY()
	
	float Speed;
	int32 Damage;	
};

UCLASS()
class SPARTA_CH3_5_SDI_API ACHProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACHProjectileBase();
	
	virtual void PostInitializeComponents() override;

public:
	void SetProjectileMovement(FVector Direction);
	
protected:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TObjectPtr<class UCHProjectileData> Data;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
	TObjectPtr<class USphereComponent> SphereComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovementComp;

	TObjectPtr<class UStaticMeshComponent> Mesh;
	
	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor
		, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
