// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameData/CHWaveData.h"
#include "CHGameMode.generated.h"

class ACHCharacterNonPlayer;
class ACHGameStateBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpawnedEnemyDeadDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaveStartDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaveEndDelegate);

/**
 * 
 */
UCLASS()
class SPARTA_CH3_5_SDI_API ACHGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACHGameMode();
	
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION()
	void OnSpawnedEnemyDead_Event();
	
	UFUNCTION()
	void OnEnemyDestroyed(AActor* DestroyedActor);
	
	UFUNCTION()
	void OnLevelEnd();
	
	UFUNCTION(BlueprintCallable, Category = "Stage|Enemy")
	void SpawnEnemy(TSubclassOf<ACHCharacterNonPlayer> SpawnedEnemyClass);
	
	UFUNCTION()
	void WaveStart();
	UFUNCTION()
	void WaveEnd();
	
	UPROPERTY(BlueprintAssignable)
	FOnSpawnedEnemyDeadDelegate OnSpawnedEnemyDead;
	
	FWaveStartDelegate OnWaveStart;
	FWaveEndDelegate OnWaveEnd;
	
	UFUNCTION(BlueprintCallable)
	float GetElapsedTime() {return ElapsedTime;}
	
private:
	float ElapsedTime;
	TArray<TObjectPtr<AActor>> SpawnedEnemies;
	
	UPROPERTY()
	TObjectPtr<ACHGameMode> CHGameMode;
	
	uint32 SpawnedActorCount;
	uint32 DestroyedActorCount;
	
	ACHGameStateBase* CHGameState;
	FTimerHandle EnemySpawnTimer;
	FCHWaveRowData* CurrentWaveRowData;
};
