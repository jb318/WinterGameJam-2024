// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIBossController.generated.h"

class UBehaviorTreeComponent;

/**
 * 
 */
UCLASS()
class TIMEWARPC_API AAIBossController : public AAIController
{
	GENERATED_BODY()

public:
	AAIBossController();
	
protected: 

	virtual void BeginPlay() override;
	
	// Possesses Pawn
	virtual void OnPossess(APawn* InPawn) override;

private: 
	// AI Blackboard and Behavior Tree Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBlackboardComponent> BlackboardComponent;
};
