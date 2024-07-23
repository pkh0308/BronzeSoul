// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class BRONZESOUL_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

// Behavior Tree
protected:
	UPROPERTY(EditDefaultsOnly, Category="BT")
	TObjectPtr<class UBlackboardData> BBData;

	UPROPERTY(EditDefaultsOnly, Category = "BT")
	TObjectPtr<class UBehaviorTree> BTData;

	UPROPERTY(EditDefaultsOnly, Category = "BT")
	class UBlackboardComponent* BBComp;

public:
	virtual void RunAI();
	virtual void StopAI();

// AI Perception
protected:
	FTimerHandle SightHandle;

	void OnSightUpdated(AActor* Actor, FAIStimulus Stimulus);

	void OnLostPlayer();
};
