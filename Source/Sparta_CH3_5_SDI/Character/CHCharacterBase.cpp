// Fill out your copyright notice in the Description page of Project Settings.


#include "CHCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "CharacterStat/CHHPComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACHCharacterBase::ACHCharacterBase()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultMeshRef(TEXT(""));
	if (DefaultMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(DefaultMeshRef.Object);
	}
	
	HPComponent = CreateDefaultSubobject<UCHHPComponent>(TEXT("Health"));
}

void ACHCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	HPComponent->OnHPChanged.AddDynamic(this, &ACHCharacterBase::OnHPChanged);
	HPComponent->OnHpZero.AddDynamic(this, &ACHCharacterBase::SetDead);
}

void ACHCharacterBase::AddMoveIgnoreActor(AActor* IgnoreActor, bool bShouldIgnore)
{
	UCapsuleComponent* CollisionComp = GetCapsuleComponent();
	CollisionComp->IgnoreActorWhenMoving(IgnoreActor, bShouldIgnore);
}

float ACHCharacterBase::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	
	HPComponent->ApplyDamage(Damage);
	
	return Damage;
}

void ACHCharacterBase::OnHPChanged(float InCurrentHP)
{
}

void ACHCharacterBase::SetDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	//PlayDeadAnimation();
	//SetActorEnableCollision(false);
}

UCHHPComponent* ACHCharacterBase::GetHPComponent()
{
	return HPComponent;
}

float ACHCharacterBase::GetCurrentHP()
{
	return HPComponent->GetCurrentHP();
}

float ACHCharacterBase::GetMaxHP()
{
	return HPComponent->GetMaxHP();
}
