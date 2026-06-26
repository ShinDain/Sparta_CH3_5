// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CHCharacterBase.generated.h"

UCLASS()
class SPARTA_CH3_5_SDI_API ACHCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACHCharacterBase();
	
	void AddMoveIgnoreActor(AActor* IgnoreActor, bool bShouldIgnore);
};
