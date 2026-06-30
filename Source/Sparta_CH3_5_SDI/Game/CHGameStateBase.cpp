// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CHGameStateBase.h"
#include "Game/CHGameMode.h"

#include "Kismet/GameplayStatics.h"

ACHGameStateBase::ACHGameStateBase()
{
	Score = 0;
	CurrentWave = 0;
	
	CurrentWaveRowData = nullptr;
	
	WaveDataTable = nullptr;
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
		
	SetCurrentWaveData(0);
}

void ACHGameStateBase::BeginPlay()
{
	Super::BeginPlay();
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
		//UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Script/Engine.World'/Game/Map/Step2.Step2'"));
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
