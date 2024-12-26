
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeWarpInterface.h"
#include "TimeObjectBase.generated.h"

class UMaterialInterface;
class UTimeComponent;

// Basic static mesh actor that can be affected by time warp mechanic
UCLASS()
class TIMEWARPC_API ATimeObjectBase : public AActor, public ITimeWarpInterface
{
	GENERATED_BODY()

public:

	ATimeObjectBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Time, meta = (AllowPrivateAccess = "true"))
	UTimeComponent* TimeComponent;

	// Interface function overrides
	virtual void TimePause() override;
	virtual void TimeEnd() override;
	virtual void TimeReverse(float ReverseSpeed) override;

	// Stored all materials used by static mesh.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Materials)
	TArray<UMaterialInterface*> OriginalMaterials;

	// The time warp material to indicate an object being manipulated.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Materials)
	UMaterialInterface* TimeMaterial;

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
};