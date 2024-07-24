// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/AI/EnemyAIController.h"

#include "BrainComponent.h"
#include "BTKey.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "PKH/Enemy/EnemyBase.h"
#include "PKH/Player/BSPlayerCharacter.h"

AEnemyAIController::AEnemyAIController()
{
	// TeamID
	TeamID = FGenericTeamId(2);

	// Components
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

	SightComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("SightComp"));
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	SightComp->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AEnemyAIController::OnSightUpdated);
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
	UE_LOG(LogTemp, Log, TEXT("[AEnemyAIController::OnSightUpdated] OnSightUpdated"));
	if (false == Actor->IsA<ABSPlayerCharacter>())
	{
		return;
	}

	AEnemyBase* Enemy = Cast<AEnemyBase>(GetPawn());
	if (nullptr == Enemy)
	{
		return;
	}

	if (Stimulus.WasSuccessfullySensed())
	{
		BBComp->SetValueAsObject(KEY_PLAYER, Actor);
		UE_LOG(LogTemp, Log, TEXT("[AEnemyAIController::OnSightUpdated] Player In Sight"));

		if (GetWorldTimerManager().IsTimerActive(SightHandle))
		{
			GetWorldTimerManager().ClearTimer(SightHandle);
		}
	}
	else
	{
		GetWorldTimerManager().SetTimer(SightHandle, this, &AEnemyAIController::OnLostPlayer, LostPlayerTime, false);
	}
}

void AEnemyAIController::OnLostPlayer()
{
	// ÀÌ¹Ì ½ÇÇàµÆ´Ù¸é ½ºÅµ
	if (nullptr == BBComp->GetValueAsObject(KEY_PLAYER))
	{
		return;
	}

	AEnemyBase* Enemy = Cast<AEnemyBase>(GetPawn());
	if (Enemy)
	{
		UE_LOG(LogTemp, Log, TEXT("[AEnemyAIController::OnSightUpdated] Lost Player"));
	}

	BBComp->SetValueAsObject(KEY_PLAYER, nullptr);
}

FGenericTeamId AEnemyAIController::GetGenericTeamId() const
{
	return TeamID;
}

void AEnemyAIController::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	TeamID = NewTeamID;
}
#pragma endregion
