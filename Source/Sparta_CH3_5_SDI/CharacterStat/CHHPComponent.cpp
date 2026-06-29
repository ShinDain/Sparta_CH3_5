// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/CHHPComponent.h"

// Sets default values for this component's properties
UCHHPComponent::UCHHPComponent()
{
	MaxHP = 100.0f;
	CurrentHP = MaxHP;
}

float UCHHPComponent::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHP;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHP(PrevHp - ActualDamage);
	if (CurrentHP <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}

	return ActualDamage;
}

void UCHHPComponent::HealHP(float InHealAmount)
{
	CurrentHP = FMath::Clamp(CurrentHP + InHealAmount, 0, MaxHP);
	OnHPChanged.Broadcast(CurrentHP);
}

void UCHHPComponent::SetHP(float NewHP)
{
	CurrentHP = FMath::Clamp<float>(NewHP, 0.0f, MaxHP);

	OnHPChanged.Broadcast(CurrentHP);
}
