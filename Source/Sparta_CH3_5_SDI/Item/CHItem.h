// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CHItem.generated.h"

UCLASS()
class SPARTA_CH3_5_SDI_API ACHItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ACHItem();

	
protected:
	TObjectPtr<USceneComponent> SceneRoot;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;
};
