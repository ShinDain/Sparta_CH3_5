// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CHHPComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float , CurrentHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHpZeroDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPARTA_CH3_5_SDI_API UCHHPComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCHHPComponent();
	
	UPROPERTY(BlueprintAssignable, Category = Stat)
	FOnHpChangedDelegate OnHPChanged;
	
	UPROPERTY(BlueprintAssignable, Category = Stat)
	FOnHpZeroDelegate OnHpZero;
	
public:
	float ApplyDamage(float InDamage);
	void HealHP(float InHealAmount);
	
	UFUNCTION(BlueprintCallable, Category = Stat)
	float GetCurrentHP() const {return CurrentHP;}
	
	UFUNCTION(BlueprintCallable, Category = Stat)
	float GetMaxHP() const { return MaxHP;} 
	
protected:
	void SetHP(float NewHP);
	
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Hp)
	float CurrentHP;
	
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Hp)
	float MaxHP;
};
