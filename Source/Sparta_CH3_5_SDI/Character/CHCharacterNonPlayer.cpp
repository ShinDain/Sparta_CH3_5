// Fill out your copyright notice in the Description page of Project Settings.


#include "CHCharacterNonPlayer.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"

ACHCharacterNonPlayer::ACHCharacterNonPlayer()
{
	HPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
	HPBar->SetupAttachment(GetMesh());
}

void ACHCharacterNonPlayer::OnHPChanged(float InCurrentHP)
{
	Super::OnHPChanged(InCurrentHP);
}

void ACHCharacterNonPlayer::SetDead()
{
	Super::SetDead();
	
	//HPBar->SetHiddenInGame(true);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->WakeAllRigidBodies();
	
	GetMesh()->AddImpulse(FVector(100.0f, -40.0f, 30.0f));
	
	OnDead.Broadcast();
	
	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), 1.0f, false);
}
