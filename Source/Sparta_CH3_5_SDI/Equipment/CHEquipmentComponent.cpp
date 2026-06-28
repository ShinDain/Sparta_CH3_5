// Fill out your copyright notice in the Description page of Project Settings.


#include "CHEquipmentComponent.h"
#include "Equipment/CHEquipmentDefinition.h"
#include "Equipment/CHEquipmentInstance.h"
#include "Character/CHCharacterBase.h"
#include "Equipment/CHWeaponInstance.h"

UCHEquipmentComponent::UCHEquipmentComponent()
{

}

void UCHEquipmentComponent::PostInitProperties()
{
	Super::PostInitProperties();
}

void UCHEquipmentComponent::EquipEquipment(UCHEquipmentDefinition* InEquipmentDefinition)
{
	if (InEquipmentDefinition == nullptr)
		return;
	
	
	// Weapon Section
	ECHEquipmentSlot Slot = InEquipmentDefinition->Slot;
	if (Slot != ECHEquipmentSlot::Weapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("Undefined Equipment Type"));
		return;
	}
		
	UnequipEquipment(Slot);
	UWorld* World = GetWorld();
	if (World)
	{
		ACHWeaponInstance* NewEquipment = World->SpawnActorDeferred<ACHWeaponInstance>(ACHWeaponInstance::StaticClass()
			, FTransform::Identity, GetOwner(), nullptr);
		NewEquipment->SetCHEquipmentDefinition(InEquipmentDefinition);
		
		ACHCharacterBase* Character = Cast<ACHCharacterBase>(GetOwner());
		USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
		FAttachmentTransformRules TransformRules(
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget,
			true
			);
		NewEquipment->AttachToComponent(CharacterMesh, TransformRules, TEXT("WeaponSocket"));
		NewEquipment->FinishSpawning(FTransform::Identity);
		OnEquipmentAttackTrigger.AddDynamic(NewEquipment, &ACHWeaponInstance::OnActive);
	}
}

void UCHEquipmentComponent::UnequipEquipment(ECHEquipmentSlot InSlot)
{
	if (InSlot != ECHEquipmentSlot::Weapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("Undefined Equipment Type"));
		return;
	}
	if (Weapon)
	{
		OnEquipmentAttackTrigger.Clear();
		Weapon->Destroy();
		Weapon = nullptr;
	}
}

void UCHEquipmentComponent::OnAttack()
{
	OnEquipmentAttackTrigger.Broadcast();
}

