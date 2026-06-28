// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/CHWeaponInstance.h"
#include "Interface/CHWeaponInterface.h"
#include "Equipment/CHWeaponDefinition.h"
#include "Projectile/CHProjectileBase.h"

ACHWeaponInstance::ACHWeaponInstance()
{
}

void ACHWeaponInstance::SetCHEquipmentDefinition(UCHEquipmentDefinition* InDefinition)
{
	Super::SetCHEquipmentDefinition(InDefinition);
	
	if (UCHWeaponDefinition* Definition = Cast<UCHWeaponDefinition>(InDefinition))
	{
		WeaponDefinition = Definition;		
		ProjectileClass = WeaponDefinition->ProjectileClass;
	}	
}

void ACHWeaponInstance::OnActive()
{
	FireProjectileWeapon();
}

void ACHWeaponInstance::FireProjectileWeapon()
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
