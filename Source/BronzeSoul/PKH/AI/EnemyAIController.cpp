// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/AI/EnemyAIController.h"

#include "BrainComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "PKH/Enemy/EnemyBase.h"
#include "PKH/Player/BSPlayerCharacter.h"

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

#pragma region Run/Stop AI
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
#pragma endregion

#pragma region AI Perception
void AEnemyAIController::OnSightUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (false == Actor->IsA<ABSPlayerCharacter>())
	{
		return;
	}

	AEnemyBase* Enemy = Cast<AEnemyBase>(GetPawn());
	if (nullptr == Enemy)
	{
		return;
	}

	if (BBComp->GetValueAsBool(TEXT("")))
	{
		return;
	}

	if (Stimulus.WasSuccessfullySensed())
	{
		

		/*BBComp->SetValueAsObject(KEY_PLAYER, Actor);
		BBComp->SetValueAsBool(KEY_PLAYER_IN_SIGHT, true);

		if (GetWorldTimerManager().IsTimerActive(SightHandle))
		{
			GetWorldTimerManager().ClearTimer(SightHandle);
		}*/
	}
	else
	{
		//GetWorldTimerManager().SetTimer(SightHandle, this, &AEnemyAIController::OnLostPlayer, TIME_LIMIT, false);
	}
}

void AEnemyAIController::OnLostPlayer()
{
	// ÀÌ¹Ì ½ÇÇàµÆ´Ù¸é ½ºÅµ
	if (nullptr == BBComp->GetValueAsObject(TEXT("")))
	{
		return;
	}

	AEnemyBase* Enemy = Cast<AEnemyBase>(GetPawn());
	if (Enemy)
	{
		
	}

	/*BBComp->SetValueAsObject(KEY_PLAYER, nullptr);
	BBComp->SetValueAsBool(KEY_PLAYER_IN_SIGHT, false);*/
}
#pragma endregion