// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBossController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AAIBossController::AAIBossController()
{
	// Create Behavior Tree Components
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("Behavior Tree Comp");
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>("Blackboard Comp");
}

void AAIBossController::BeginPlay()
{
	Super::BeginPlay();

	// Gets the behavior tree if it has been initialized in Unreal
	if (IsValid(BehaviorTree.Get())) {
		RunBehaviorTree(BehaviorTree.Get());
		BehaviorTreeComponent->StartTree(*BehaviorTree.Get());
	}
}

void AAIBossController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// When Pawn is possessed, initialze blackboard if blackboard component and behavior tree component are both valid
	if (IsValid(Blackboard.Get()) && IsValid(BehaviorTree.Get())) {
		Blackboard->InitializeBlackboard(*BehaviorTree.Get()->BlackboardAsset.Get());
	}
}
