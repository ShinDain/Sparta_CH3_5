// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameData/CHWaveData.h"
#include "CHGameStateBase.generated.h"

class ACHCharacterNonPlayer;
class ACHGameMode;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScoreChangedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelEndDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaveDataUpdatedDelegate);

/**
 * 
 */
UCLASS()
class SPARTA_CH3_5_SDI_API ACHGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ACHGameStateBase();
	
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnEnemyDead();
	
	void SetCurrentWaveData(int32 NewWave);
	void NextWaveData();
	
	FCHWaveRowData* CurrentWaveRowData;
	
	UPROPERTY(BlueprintAssignable, Category = "Stage|Score")
	FScoreChangedDelegate OnScoreChanged;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stage|Score")
	float Score;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stage|Enemy")
	TSubclassOf<ACHCharacterNonPlayer> SpawnedEnemyClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stage")
	TObjectPtr<UDataTable> WaveDataTable;	

	UPROPERTY(BlueprintReadOnly, Category = "Stage")
	int32 CurrentWave;
	
	UPROPERTY(BlueprintAssignable)
	FLevelEndDelegate OnLevelEnd;
	
	FWaveDataUpdatedDelegate OnWaveDataUpdated;
};
