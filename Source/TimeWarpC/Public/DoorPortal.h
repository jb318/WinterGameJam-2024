// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorPortal.generated.h"

UCLASS()
class TIMEWARPC_API ADoorPortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorPortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Opens actor when you clicked all buttons
	UFUNCTION(BlueprintCallable)
	void unlockDoor();

	int buttonGoal;
	
	int buttonsClicked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool canEnter = true;

};
