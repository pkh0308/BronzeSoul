// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/AI/EnemyAIController.h"

#include "BrainComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"

AEnemyAIController::AEnemyAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBDataRef(TEXT("/Script/AIModule.BlackboardData'/Game/PKH/Enemy/AI/BB_Enemy.BB_Enemy'"));
	if(BBDataRef.Object)
	{
		BBData = BBDataRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTDataRef(TEXT("/Script/AIModule.BehaviorTree'/Game/PKH/Enemy/AI/BT_Enemy.BT_Enemy'"));
	if (BTDataRef.Object)
	{
		BTData = BTDataRef.Object;
	}
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


}

void AEnemyAIController::RunAI()
{
	BBComp = Blackboard;
	if(UseBlackboard(BBData, BBComp))
	{
		bool result = RunBehaviorTree(BTData);

		// Initialize Keys

	}
}

void AEnemyAIController::StopAI()
{
	UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent);
	if(BTComp)
	{
		BTComp->StopTree();
	}
}
