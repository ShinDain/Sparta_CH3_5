// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/CHHPInterface.h"
#include "CHCharacterBase.generated.h"

class UCHHPComponent;

UCLASS()
class SPARTA_CH3_5_SDI_API ACHCharacterBase : public ACharacter, public ICHHPInterface
{
	GENERATED_BODY()

public:
	ACHCharacterBase();
	
	virtual void PostInitializeComponents() override;
	void AddMoveIgnoreActor(AActor* IgnoreActor, bool bShouldIgnore);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat)
	TObjectPtr<UCHHPComponent> HPComponent;
	
protected:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	UFUNCTION()
	virtual void OnHPChanged(float InCurrentHP);
	
	UFUNCTION()
	virtual void SetDead();
	
	// ICHHPInterface
public:
	virtual UCHHPComponent* GetHPComponent() override;
	virtual float GetCurrentHP() override;
	virtual float GetMaxHP() override;
};
