
#pragma once

#include "TimeWarpInterface.generated.h"

// Interface for time manipulation
UINTERFACE(MinimalAPI, Blueprintable)
class UTimeWarpInterface : public UInterface
{
	GENERATED_BODY()
};

// Interface for time manipulation
class ITimeWarpInterface
{
	GENERATED_BODY()

public:

	// Used for pausing the object in time
	UFUNCTION()
	virtual void TimePause() = 0;

	// Used for ending time manipulation on the object
	UFUNCTION()
	virtual void TimeEnd() = 0;

	// Used for reversing time at a set speed on the object.
	UFUNCTION()
	virtual void TimeReverse(float ReverseSpeed) = 0;
};