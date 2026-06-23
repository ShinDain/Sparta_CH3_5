// Fill out your copyright notice in the Description page of Project Settings.


#include "CHGameMode.h"
#include "Character/CHCharacterBase.h"

ACHGameMode::ACHGameMode()
{
	DefaultPawnClass = ACHCharacterBase::StaticClass();
	
}
