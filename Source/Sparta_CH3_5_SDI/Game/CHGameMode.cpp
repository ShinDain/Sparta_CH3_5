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
}

void ACHGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CHGameState = GetGameState<ACHGameStateBase>();
	if (CHGameState)
	{
		CHGameState->OnLevelEnd.AddDynamic(this, &ACHGameMode::OnLevelEnd);
		CHGameState->OnWaveDataUpdated.AddDynamic(this, &ACHGameMode::WaveStart);
	}
}

void ACHGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
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

void ACHGameMode::OnLevelEnd()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Script/Engine.World'/Game/Map/Step2.Step2'"));
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
	
	if (CHGameState == nullptr)
		return;
	
	CurrentWaveRowData = CHGameState->CurrentWaveRowData;
	GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimer);
	
	SpawnedActorCount = 0;
	DestroyedActorCount = 0;
	ElapsedTime = 0;
	
	float Interval = 1.0f;
	
	FCHWaveRowData* CurrentRowData = CHGameState->CurrentWaveRowData;
	if (CurrentRowData)
		Interval = CurrentRowData->SpawnInterval;
	
	FTimerDelegate SpawnDelegate;
	SpawnDelegate.BindUObject(this, &ACHGameMode::SpawnEnemy, CHGameState->SpawnedEnemyClass);
	
	GetWorld()->GetTimerManager().SetTimer(EnemySpawnTimer, SpawnDelegate, Interval, true);
}

void ACHGameMode::WaveEnd()
{
	if (CHGameState)
	{
		CHGameState->NextWaveData();
		CurrentWaveRowData = CHGameState->CurrentWaveRowData;
	}
			
	OnWaveEnd.Broadcast();
}
