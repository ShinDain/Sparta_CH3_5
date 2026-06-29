// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CHGameStateBase.h"
#include "Game/CHGameMode.h"

ACHGameStateBase::ACHGameStateBase()
{
	Score = 0;
	CurrentWave = 0;
}

void ACHGameStateBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	UWorld* World = GetWorld();
	if (World)
	{
		ACHGameMode* CHGameMode = Cast<ACHGameMode>(World->GetAuthGameMode());
		if (CHGameMode)
		{
			CHGameMode->OnSpawnedEnemyDead.AddDynamic(this, &ACHGameStateBase::OnEnemyDead);
		}
	}
}

void ACHGameStateBase::BeginPlay()
{
	Super::BeginPlay();
	
	SetCurrentWaveData(0);
}

void ACHGameStateBase::OnEnemyDead()
{
	Score += 1;
	OnScoreChanged.Broadcast();
}

void ACHGameStateBase::SetCurrentWaveData(int32 NewWave)
{
	CurrentWave = NewWave;
	if (CurrentWave >= WaveDataTable->GetRowMap().Num())
	{
		OnLevelEnd.Broadcast();
		return;
	}
	
	if (WaveDataTable)
	{
		check(WaveDataTable->GetRowMap().Num() > 0);

		TArray<FName> NameArray = WaveDataTable->GetRowNames();
		CurrentWaveRowData = WaveDataTable->FindRow<FCHWaveRowData>(NameArray[CurrentWave], TEXT("Loading Row Data"));
		
		OnWaveDataUpdated.Broadcast();
	}
}

void ACHGameStateBase::NextWaveData()
{
	SetCurrentWaveData(CurrentWave + 1);
}
