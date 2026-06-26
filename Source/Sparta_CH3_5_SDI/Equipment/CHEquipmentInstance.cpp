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
	ProjectileClass = EquipmentDefinition->ProjectileClass;
}

void ACHEquipmentInstance::OnAttack()
{
	FireProjectileWeapon();
}

void ACHEquipmentInstance::FireProjectileWeapon()
{
	UWorld* World = GetWorld();
	ensure(World);
	FTransform SpawnTransform(GetActorLocation());
	
	if (ProjectileClass)
	{
		FVector Direction(GetOwner()->GetActorForwardVector());
		
		if (ICHWeaponInterface* WeaponInterface  = Cast<ICHWeaponInterface>(GetOwner()))
		{
			FHitResult HitResult = WeaponInterface->PerformLineTraceForProjectileWeapon();

			if(HitResult.GetActor() != nullptr)
			{
				FVector StartLocation = GetActorLocation();
				FVector EndLocation = HitResult.ImpactPoint;
				Direction = EndLocation - StartLocation;
				Direction.Normalize();	
			}
		}
		
		ACHProjectileBase* NewProjectile = World->SpawnActorDeferred<ACHProjectileBase>
			(ProjectileClass, SpawnTransform, GetOwner(), nullptr);
		if (NewProjectile)
		{			
			NewProjectile->SetProjectileMovement(Direction);
			NewProjectile->FinishSpawning(SpawnTransform);
		}		
	}
}
