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
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverDelegate);

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
	
	void CheckWaveEnd();
	
	UFUNCTION()
	void OnLevelEnd();
	
	UFUNCTION(BlueprintCallable, Category = "Stage|Enemy")
	void SpawnEnemy(TSubclassOf<ACHCharacterNonPlayer> SpawnedEnemyClass);
	
	UFUNCTION(BlueprintCallable)
	void WaveStart();
	UFUNCTION()
	void WaveEnd();
	
	void GameOver();
	
	UPROPERTY(BlueprintAssignable)
	FOnSpawnedEnemyDeadDelegate OnSpawnedEnemyDead;
	
	UPROPERTY(BlueprintAssignable)
	FWaveStartDelegate OnWaveStart;
	
	UPROPERTY(BlueprintAssignable)
	FWaveEndDelegate OnWaveEnd;
	
	UPROPERTY(BlueprintAssignable)
	FGameOverDelegate OnGameOver;
	
	UFUNCTION(BlueprintCallable)
	float GetElapsedTime() {return ElapsedTime;}
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<ACHGameStateBase> CHGameState;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Level)
	FName NextLevelName;
	
private:
	uint8 bWaveRunning:1;
	float ElapsedTime;
	
	uint32 SpawnedActorCount;
	uint32 DestroyedActorCount;
	
	FTimerHandle WaveTimer;
	FTimerHandle EnemySpawnTimer;
	FCHWaveRowData* CurrentWaveRowData;
	
	UPROPERTY()
	TArray<TObjectPtr<AActor>> SpawnedEnemies;	
};
