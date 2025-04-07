// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ThirdPersonCharacter.h"
#include "TimeWarpCPlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class TIMEWARPC_API ATimeWarpCPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATimeWarpCPlayerController();

protected:

	virtual void BeginPlay() override;

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* InteractAction;

public:
	// Sets up input mapping context on character controller possesses
	virtual void SetupInputComponent() override;

	// Player character class reference
	UPROPERTY()
	AThirdPersonCharacter* PlayerCharacter;

private:
	// Input events
	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void Jump(const FInputActionValue& value);
	void Interact(const FInputActionValue& value);
	
};
