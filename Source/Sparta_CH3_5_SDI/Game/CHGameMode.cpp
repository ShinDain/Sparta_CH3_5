// Fill out your copyright notice in the Description page of Project Settings.


#include "CHGameMode.h"
#include "Character/CHCharacterBase.h"
#include "Character/CHCharacterNonPlayer.h"
#include "GameData/CHWaveData.h"
#include "Game/CHGameStateBase.h"
#include "Kismet/GameplayStatics.h"

ACHGameMode::ACHGameMode()
{
	DefaultPawnClass = ACHCharacterBase::StaticClass();
	PrimaryActorTick.bCanEverTick  = true;
	bWaveRunning = false;

	CHGameState = nullptr;
	CurrentWaveRowData = nullptr;
}

void ACHGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CHGameState = GetGameState<ACHGameStateBase>();
	if (CHGameState)
	{
		CHGameState->OnLevelEnd.AddDynamic(this, &ACHGameMode::OnLevelEnd);
		//CHGameState->OnWaveDataUpdated.AddDynamic(this, &ACHGameMode::WaveStart);
	}
}

void ACHGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (bWaveRunning)
		ElapsedTime += DeltaSeconds;
}

void ACHGameMode::OnSpawnedEnemyDead_Event()
{
	OnSpawnedEnemyDead.Broadcast();
}

void ACHGameMode::OnEnemyDestroyed(AActor* DestroyedActor)
{
	DestroyedActorCount += 1;
	
	if (ElapsedTime >= CurrentWaveRowData->WaveTime)
	{
		if (DestroyedActorCount >= SpawnedActorCount)
		{
			WaveEnd();
		}
	}
}

void ACHGameMode::CheckWaveEnd()
{
	if (ElapsedTime >= CurrentWaveRowData->WaveTime)
	{
		if (DestroyedActorCount >= SpawnedActorCount)
		{
			WaveEnd();
		}
	}
}

void ACHGameMode::OnLevelEnd()
{
	if (GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(EnemySpawnTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimer);
	}
	for (AActor* Enemy : SpawnedEnemies)
	{
		if (IsValid(Enemy))
		{
			Enemy->Destroy();
		}
	}

	SpawnedEnemies.Empty();
	
	if (NextLevelName.IsNone())
	{
		GameOver();
	}
	else
	{
		UGameplayStatics::OpenLevel(GetWorld(), NextLevelName);
	}
}

void ACHGameMode::SpawnEnemy(TSubclassOf<ACHCharacterNonPlayer> SpawnedEnemyClass)
{	
	if (CurrentWaveRowData &&
		ElapsedTime >= CurrentWaveRowData->WaveTime)
		return;
	
	if (SpawnedEnemyClass)
	{
		FVector Location(FMath::RandRange(-1000,1000)
			,FMath::RandRange(-1000,1000)
			,0);
		
		UWorld* World = GetWorld();
		if (World == nullptr)
			return;
		
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		SpawnParameters.Owner = this;
		FRotator Rotation;
		ACHCharacterNonPlayer* NewEnemy = World->SpawnActor<ACHCharacterNonPlayer>(
			SpawnedEnemyClass, Location, Rotation, SpawnParameters);
		
		NewEnemy->OnDead.AddUObject(this, &ACHGameMode::OnSpawnedEnemyDead_Event);
		NewEnemy->OnDestroyed.AddDynamic(this, &ACHGameMode::OnEnemyDestroyed);
		
		if (NewEnemy)
		{
			SpawnedEnemies.Add(NewEnemy);
			SpawnedActorCount += 1;
		}
	}
}

void ACHGameMode::WaveStart()
{
	OnWaveStart.Broadcast();
	bWaveRunning = true;
	
	if (CHGameState == nullptr)
		return;
	
	CurrentWaveRowData = CHGameState->CurrentWaveRowData;
	GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimer);
	
	SpawnedActorCount = 0;
	DestroyedActorCount = 0;
	ElapsedTime = 0;
	
	float Interval = 1.0f;
	
	if (CurrentWaveRowData)
		Interval = CurrentWaveRowData->SpawnInterval;
	
	FTimerDelegate SpawnDelegate;
	SpawnDelegate.BindUObject(this, &ACHGameMode::SpawnEnemy, CHGameState->SpawnedEnemyClass);
	
	GetWorld()->GetTimerManager().SetTimer(EnemySpawnTimer, SpawnDelegate, Interval, true);
	
	float WaveTime = CurrentWaveRowData->WaveTime;
	GetWorld()->GetTimerManager().SetTimer(WaveTimer, FTimerDelegate::CreateUObject(this, &ACHGameMode::CheckWaveEnd)
		, WaveTime, false);
}

void ACHGameMode::WaveEnd()
{
	OnWaveEnd.Broadcast();
	bWaveRunning = false;
	
	if (CHGameState)
	{
		CHGameState->NextWaveData();
		CurrentWaveRowData = CHGameState->CurrentWaveRowData;
	}
	
	
}

void ACHGameMode::GameOver()
{
	OnGameOver.Broadcast();
}
