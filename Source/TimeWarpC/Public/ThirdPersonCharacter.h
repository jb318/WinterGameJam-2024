// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ThirdPersonCharacter.generated.h"

UCLASS()
class TIMEWARPC_API AThirdPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AThirdPersonCharacter();
	
	// Constructor Components

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Enhanced input mapping context and actions
	// Need this for 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* PlayerInputContext;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
