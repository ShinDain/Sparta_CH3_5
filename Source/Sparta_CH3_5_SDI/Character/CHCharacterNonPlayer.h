// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CHCharacterBase.h"
#include "CHCharacterNonPlayer.generated.h"

DECLARE_MULTICAST_DELEGATE(FNonPlayerDeadDelegate);

/**
 * 
 */
UCLASS()
class SPARTA_CH3_5_SDI_API ACHCharacterNonPlayer : public ACHCharacterBase
{
	GENERATED_BODY()
	
public:
	ACHCharacterNonPlayer();
	
	FNonPlayerDeadDelegate OnDead;
	
protected:
	virtual void OnHPChanged(float InCurrentHP) override;
	virtual void SetDead() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget)
	TObjectPtr<class UWidgetComponent> HPBar;

};
