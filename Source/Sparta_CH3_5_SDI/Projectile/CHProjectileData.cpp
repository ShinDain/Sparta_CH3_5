// Fill out your copyright notice in the Description page of Project Settings.


#include "CHProjectileData.h"

UCHProjectileData::UCHProjectileData()
{
	Speed = 500.0f;
	Damage = 0.0f;
	Scale = FVector(1.0f,1.0f,1.0f);
	Offset = FVector::Zero();
}
