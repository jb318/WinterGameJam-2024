// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimeWarpCGameMode.generated.h"

UCLASS(minimalapi)
class ATimeWarpCGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATimeWarpCGameMode();

	// Used for setting the max amount of time to be tracked. Could be altered to track movement instead of time
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Time)
	float MaxTimeTracked = 120.f;

	// How often a time snapshot is taken. By default one is taken every 30 milliseconds
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Time)
	float TrackFrequency = 0.03f;
};



