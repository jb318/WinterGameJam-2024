
#pragma once

#include "CoreMinimal.h"
#include "TimeWarpData.generated.h"

// Struct that contains information needed for tracking time snaps
USTRUCT(BlueprintType)
struct FTimeSnap
{
	GENERATED_BODY()

	// The global transform of the tracked object
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Time)
	FTransform SnapTransform;

	// The linear velocity is the directional speed in which the object is traveling at the time of the snap
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Time)
	FVector SnapLinearVelocity;

	// The angular velocity can be thought of as the rotational velocity of the object at the time of the snap.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Time)
	FVector SnapAngularVelocity;
};