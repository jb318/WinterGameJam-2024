
#pragma once

#include "CoreMinimal.h"
#include "TimeWarpData.h"
#include "TimeComponent.generated.h"

// The time warp component
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TIMEWARPC_API UTimeComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// Default Constructor
	UTimeComponent();

	// Obtains information from the gamemode
	void Setup();

	// The looping function for tracking time snaps, frozen time, and reversing time.
	void TimeProgress();

	// Calculate the max time snaps to take for tracker
	void StartTimeTracker();

	// Reverses time on the owning actor
	void ReverseTime();

	// Pauses time on the owning actor
	void PauseTime();

	// Records a time snap of the owning actor
	void RecordTime();

	// Pauses physics on the root component of the owning actor
	void PausePhysics(bool ShouldPause);

	// Applys the time snap given. Used when freezing and unfreezing an object
	void ApplyTime(FTimeSnap TimeApplied);

	// Interpolates the transforms saved in the time snaps. Used to more smoothly reverse time and reduce jitter while reversing.
	void ApplyTimeInterpolated(FTimeSnap TimeSnapBegin, FTimeSnap TimeSnapEnd);

	// Stops manipulating the owning actor.
	void StopManipulation();


protected:

	virtual void BeginPlay() override;

public:

	// Time used for looping the timeprogress function
	 FTimerHandle SnapTimer;

	 // Array holding the saved Time snaps of the actor
	 UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Time)
	 TArray<FTimeSnap> TimeSnaps;

	 // Whether the object is frozen in time
	 UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Time)
	 bool bIsFrozen;

	 // The root component of the owning actor
	 UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Time)
	 UPrimitiveComponent* OwnerRoot;

	 // Whether the object is currently reversing in time or should be reversing in time
	 UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Time)
	 bool bIsRewinding;

	 // The maximum elapsed time tracked. Obtained from gamemode by default
	 UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Time)
	 float MaxTimeTracked;

	 // The maximum time snaps to collect. Obtained by dividng MaxTimeTracked by SnapFrequency
	 UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Time)
	 float MaxSnaps;

	 // The speed in which to rewind
	 UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Time)
	 float RewindSpeed;

	 // float value used for smooth interpolation between time snaps transforms when reversing
	 UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Time)
	 float Progress;

	 // the frequency per second in which to track a time snap
	 UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Time)
	 float SnapFrequency;
};