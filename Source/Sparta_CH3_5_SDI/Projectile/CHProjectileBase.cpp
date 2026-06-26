// Fill out your copyright notice in the Description page of Project Settings.


#include "CHProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CHProjectileData.h"
#include "Components/SphereComponent.h"
#include "Physics/CHCollision.h"
#include "Character/CHCharacterBase.h"

// Sets default values
ACHProjectileBase::ACHProjectileBase()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);
	SphereComponent->SetCollisionProfileName(CPROFILE_CHPROJECTILE);
	SphereComponent->OnComponentHit.AddDynamic(this, &ACHProjectileBase::OnProjectileHit);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	Mesh->SetupAttachment(RootComponent);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComp->ProjectileGravityScale = 0.0f;
}

void ACHProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	if (Data)
	{
		Mesh->SetStaticMesh(Data->Mesh);
		Mesh->SetRelativeScale3D(Data->Scale);
		Mesh->AddRelativeLocation(Data->Offset);
	}
	AActor* OwnerActor = GetOwner();
	if (OwnerActor)
	{
		SphereComponent->IgnoreActorWhenMoving(OwnerActor, true);
		
		ACHCharacterBase* OwnerCharacter = Cast<ACHCharacterBase>(OwnerActor);
		if (OwnerCharacter)
		{
			OwnerCharacter->AddMoveIgnoreActor(this, true);
		}
	}
	
	SetLifeSpan(10.0f);
}

void ACHProjectileBase::SetProjectileMovement(FVector Direction)
{
	if (Data
		&& ProjectileMovementComp)
	{
		FVector Velocity = Direction * Data->Speed;
		ProjectileMovementComp->Velocity = Velocity;
	}
}

void ACHProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor
                                        , UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *OtherActor->GetName());
	
	if (OtherActor == GetOwner())
		return;
	
	Mesh->SetHiddenInGame(true);
	Destroy();	
}


