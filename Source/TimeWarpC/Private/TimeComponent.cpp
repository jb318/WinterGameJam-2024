#include "TimeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimeWarpCGameMode.h"

UTimeComponent::UTimeComponent()
{

}

void UTimeComponent::Setup()
{
	if (ATimeWarpCGameMode* GameMode = Cast<ATimeWarpCGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		MaxTimeTracked = GameMode->MaxTimeTracked;
		SnapFrequency = GameMode->TrackFrequency;

		// Casts owner root component to primitive component for more universal control regardless of the exact root component
		OwnerRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	}
}

void UTimeComponent::TimeProgress()
{
	if (bIsRewinding)
	{
		ReverseTime();
	}
	else if (bIsFrozen)
	{
		PauseTime();
	}
	else
	{
		RecordTime();
	}
}

void UTimeComponent::StartTimeTracker()
{
	MaxSnaps = MaxTimeTracked / SnapFrequency;
}

void UTimeComponent::ReverseTime()
{
	if (TimeSnaps.IsValidIndex(TimeSnaps.Num() - 2))
	{
		Progress = UKismetMathLibrary::FClamp(Progress + RewindSpeed, 0.f, 1.f);

		ApplyTimeInterpolated(TimeSnaps.Last(), TimeSnaps[TimeSnaps.Num() - 2]);

		if (Progress >= 1.f)
		{
			Progress = 0.f;

			// Removes used time snaps. This prevents "fast-forwarding" back through time once reversed. Could be removed and altered.
			TimeSnaps.RemoveAt(TimeSnaps.Num() - 1);
		}
	}
	else
	{
		ApplyTime(TimeSnaps[TimeSnaps.Num() - 1]);
		bIsRewinding = false;
	}
}

void UTimeComponent::PauseTime()
{
	// Pauses based on the last time snap and pauses physics on the object. Can still collide with objects while frozen.
	PausePhysics(true);
	ApplyTime(TimeSnaps.Last());
}

void UTimeComponent::RecordTime()
{
	if (TimeSnaps.Num() >= MaxSnaps)
	{
		TimeSnaps.RemoveAt(0);
	}

	TimeSnaps.Add(FTimeSnap({
		GetOwner()->GetActorTransform(),
		OwnerRoot->GetPhysicsLinearVelocity(),
		OwnerRoot->GetPhysicsAngularVelocityInRadians() }));

}

void UTimeComponent::PausePhysics(bool ShouldPause)
{
	if (ShouldPause)
	{
		OwnerRoot->SetSimulatePhysics(false);
	}
	else
	{
		OwnerRoot->SetSimulatePhysics(true);
	}
}

void UTimeComponent::ApplyTime(FTimeSnap TimeApplied)
{
	GetOwner()->SetActorTransform(TimeApplied.SnapTransform);
	OwnerRoot->SetPhysicsLinearVelocity(TimeApplied.SnapLinearVelocity);
	OwnerRoot->SetPhysicsAngularVelocityInRadians(TimeApplied.SnapAngularVelocity);
}

void UTimeComponent::ApplyTimeInterpolated(FTimeSnap TimeSnapBegin, FTimeSnap TimeSnapEnd)
{
	GetOwner()->SetActorTransform(UKismetMathLibrary::TLerp(TimeSnapBegin.SnapTransform, TimeSnapEnd.SnapTransform, Progress));
}

void UTimeComponent::StopManipulation()
{
	bIsRewinding = false;
	bIsFrozen = false;

	PausePhysics(false);
	// Applies the last saved time snap to apply the latest physics on the object. This creates more accurate recreations of moments in time.
	ApplyTime(TimeSnaps.Last());
}

void UTimeComponent::BeginPlay()
{
	Super::BeginPlay();

	Setup();
	StartTimeTracker();

	GetWorld()->GetTimerManager().SetTimer(SnapTimer, this, &UTimeComponent::TimeProgress, SnapFrequency, true, 0.f);

}
