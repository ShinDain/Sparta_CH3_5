// Fill out your copyright notice in the Description page of Project Settings.


#include "CHCharacterBase.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ACHCharacterBase::ACHCharacterBase()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultMeshRef(TEXT(""));
	if (DefaultMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(DefaultMeshRef.Object);
	}
	
	GetCapsuleComponent();
}

void ACHCharacterBase::AddMoveIgnoreActor(AActor* IgnoreActor, bool bShouldIgnore)
{
	UCapsuleComponent* CollisionComp = GetCapsuleComponent();
	CollisionComp->IgnoreActorWhenMoving(IgnoreActor, bShouldIgnore);
}
