// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CHWaveData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FCHWaveRowData: public FTableRowBase
{
	GENERATED_BODY()
	
public:
	FCHWaveRowData() : SpawnCnt(1), SpawnInterval(1.0f), MaxSpawnEnemy(1), WaveLevel(1) {}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wave, meta = (ClampMin = 1, UIMin = 1))
	int32 SpawnCnt;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wave, meta = (ClampMin = 0.1f, ClampMax = 5.0f, UIMin = 0.1f, UIMax = 5.0f))
	float SpawnInterval;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wavem, meta = (ClampMin = 1, UIMin = 1))
	int32 MaxSpawnEnemy;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wave, meta = (ClampMin = 1, UIMin = 1))
	int32 WaveLevel;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wave, meta = (ClampMin = 1, UIMin = 1))
	float WaveTime;	
	
};
