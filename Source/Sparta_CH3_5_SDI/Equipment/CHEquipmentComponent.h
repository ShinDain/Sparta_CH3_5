// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Equipment/CHEquipmentDefinition.h"
#include "CHEquipmentComponent.generated.h"

class ACHWeaponInstance;
class UCHWeaponDefinition;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentAttackTrigger);
DECLARE_MULTICAST_DELEGATE(FOnWeaponAttackSuccess);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPARTA_CH3_5_SDI_API UCHEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCHEquipmentComponent();
	
	virtual void PostInitProperties() override;
	
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void EquipEquipment(UCHEquipmentDefinition* InEquipmentDefinition);
	
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void UnequipEquipment(ECHEquipmentSlot InSlot);
	
	UFUNCTION()
	void OnAttack();
	
	FEquipmentAttackTrigger OnEquipmentAttackTrigger;
	FOnWeaponAttackSuccess OnWeaponAttackSuccessed;
	
	// Weapon Section
public:
	ACHWeaponInstance* GetWeaponInstance() const { return Weapon;}
	const UCHWeaponDefinition* GetWeaponDefinition() const;
	
protected:
	void OnWeaponAttackSuccessed_Implement();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	TObjectPtr<ACHWeaponInstance> Weapon;
	
};
