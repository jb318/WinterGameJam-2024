// Copyright Epic Games, Inc. All Rights Reserved.

#include "TimeWarpCCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "TimeWarpInterface.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "DoorPortal.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATimeWarpCCharacter

ATimeWarpCCharacter::ATimeWarpCCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	GunMesh->SetupAttachment(Mesh1P, "GripPoint");

	// Instantiate Levels Array with each game level
	levels.Add("Asian_Village_Demo");
	levels.Add("Gym_Map");
}

void ATimeWarpCCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

//////////////////////////////////////////////////////////////////////////// Input

void ATimeWarpCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATimeWarpCCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATimeWarpCCharacter::Look);

		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ATimeWarpCCharacter::Shoot);

		EnhancedInputComponent->BindAction(TimeSpeedAction, ETriggerEvent::Triggered, this, &ATimeWarpCCharacter::TimeSpeed);

		EnhancedInputComponent->BindAction(ResumeTimeAction, ETriggerEvent::Triggered, this, &ATimeWarpCCharacter::ResumeTime);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ATimeWarpCCharacter::EngageObject);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATimeWarpCCharacter::SwitchLevel()
{
	// Gets the name of the current map
	FString current = GetWorld()->GetMapName();
	current.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	// Open Level 
	UGameplayStatics::OpenLevel(GetWorld(), newMap );
}


void ATimeWarpCCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ATimeWarpCCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATimeWarpCCharacter::TimeSpeed(const FInputActionValue& Value)
{
	if (!ActiveTargets.IsEmpty())
	{
		RewindTimeSpeed = UKismetMathLibrary::FClamp(RewindTimeSpeed + (Value.Get<float>() * 0.1f), 0.f, 2.f);

		for (int x = 0; x < ActiveTargets.Num(); x++)
		{
			Cast<ITimeWarpInterface>(ActiveTargets[x])->TimeReverse(RewindTimeSpeed);
		}
	}
}

void ATimeWarpCCharacter::ResumeTime(const FInputActionValue& Value)
{
	if (!ActiveTargets.IsEmpty())
	{
		for (int x = 0; x < ActiveTargets.Num(); x++)
		{
			Cast<ITimeWarpInterface>(ActiveTargets[x])->TimeEnd();
		}

		ActiveTargets.Empty();
	}
}

void ATimeWarpCCharacter::Shoot(const FInputActionValue& Value)
{
	if (FireAnimation != nullptr)
	{
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}

	FVector StartLocation = GunMesh->GetSocketLocation("Ammo");
	FVector EndLocation = StartLocation + (FirstPersonCameraComponent->GetForwardVector() * 1500.f);
	FHitResult* Hit = new FHitResult();

	UKismetSystemLibrary::SphereTraceSingle(this, StartLocation, EndLocation, 12.f, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, TArray<AActor*>(), EDrawDebugTrace::None, *Hit, true);

	if (Hit->GetActor() != nullptr)
	{
		if (Hit->GetActor()->GetClass()->ImplementsInterface(UTimeWarpInterface::StaticClass()))
		{
			ActiveTargets.Add(Hit->GetActor());
			RewindTimeSpeed = 0.f;
			Cast<ITimeWarpInterface>(Hit->GetActor())->TimePause();
		}
		
	}

}

void ATimeWarpCCharacter::EngageObject(const FInputActionValue& Value)
{
	if (FireAnimation != nullptr)
	{
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}

	FVector StartLocation = GunMesh->GetSocketLocation("Ammo");
	FVector EndLocation = StartLocation + (FirstPersonCameraComponent->GetForwardVector() * 1500.f);
	FHitResult* Hit = new FHitResult();

	UKismetSystemLibrary::SphereTraceSingle(this, StartLocation, EndLocation, 12.f, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, TArray<AActor*>(), EDrawDebugTrace::None, *Hit, true);

	if (Hit->GetActor() != nullptr)
	{
		
		ADoorPortal* door = Cast<ADoorPortal>(Hit->GetActor());
		if (door)
		{
			
			if (door->canEnter)
			{
				// Switches Level while opening door
				door->AddActorWorldRotation(FRotator(0, 90, 0));
				SwitchLevel();

				// Not working yet
				door->canEnter = false;
				
			} 
			
		}
	}
}
