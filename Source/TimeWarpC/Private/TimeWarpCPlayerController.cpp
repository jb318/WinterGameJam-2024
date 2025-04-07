// Copyright Epic Games, Inc. All Rights Reserved.


#include "TimeWarpCPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

ATimeWarpCPlayerController::ATimeWarpCPlayerController()
{
	// Empty
}

void ATimeWarpCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Gets reference to player character
	PlayerCharacter = Cast<AThirdPersonCharacter>(GetCharacter());

	// Cast to the controller assigned to player character class to check if it matches this class
	if (ATimeWarpCPlayerController* PC = Cast<ATimeWarpCPlayerController>(this)) {
		// Get the local subsystem that is being used by the player character class
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer())) {
			// Check if input context is good
			if (InputMappingContext) {
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}

void ATimeWarpCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Checking controller to see if it is valid
	if (ATimeWarpCPlayerController* PC = Cast<ATimeWarpCPlayerController>(this)) {
		// Checking mapping context to see if it is valid
		if (UEnhancedInputComponent* Subsystem = Cast<UEnhancedInputComponent>(InputComponent)) {
			// Check if each of the inputs are assigned to mapping context and binds action if so
			if (MoveAction) {
				// Grabs the subsystem we got from the player and binds each input action so we call the function everytime the value or input pairing is clicked
				Subsystem->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATimeWarpCPlayerController::Move);
				
			}
			if (LookAction) {
				Subsystem->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATimeWarpCPlayerController::Look);
			}
			if (JumpAction) {
				Subsystem->BindAction(JumpAction, ETriggerEvent::Started, this, &ATimeWarpCPlayerController::Jump);
			}
			if (InteractAction) {
				Subsystem->BindAction(InteractAction, ETriggerEvent::Started, this, &ATimeWarpCPlayerController::Interact);
			}
		}
	}
}

void ATimeWarpCPlayerController::Move(const FInputActionValue& value)
{
	FVector2D MovementVector = value.Get<FVector2D>();

	if (APawn* ControlledPawn = GetPawn()) {
		// Sets the camera rotation for possessed character 
		FRotator CameraRotation = GetControlRotation();
		FRotator YawRotation(0.f, CameraRotation.Yaw, 0.f);

		// Gets coordinate values in one dimensional space, one for forward and back, other for left and right
		FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Adds that movement to controlled character to have it move in the world
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}

	
}

void ATimeWarpCPlayerController::Look(const FInputActionValue& value)
{
	// Parse input value for looking
	FVector2D LookAxisVector = value.Get<FVector2D>();

	if (APawn* ControlledPawn = GetPawn()) {
		// Add controller yaw and pitch input
		AddYawInput(LookAxisVector.X);
		AddPitchInput(LookAxisVector.Y);
	}
}

void ATimeWarpCPlayerController::Jump(const FInputActionValue& value)
{
	if (PlayerCharacter) {
		PlayerCharacter->Jump();
	}
}

void ATimeWarpCPlayerController::Interact(const FInputActionValue& value)
{
	// Get overlapping actors is probably the best functionality for interact on basic input mapping context

}
