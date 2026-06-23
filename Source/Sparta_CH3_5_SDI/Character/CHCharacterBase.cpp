// Fill out your copyright notice in the Description page of Project Settings.


#include "CHCharacterBase.h"

// Sets default values
ACHCharacterBase::ACHCharacterBase()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultMeshRef(TEXT(""));
	if (DefaultMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(DefaultMeshRef.Object);
	}
	
	GetCapsuleComponent();
}