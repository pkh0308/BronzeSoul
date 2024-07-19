
#include "PKH/Enemy/EnemyBase.h"

#include "PKH/AI/EnemyAIController.h"
#include "Runtime/AIModule/Classes/AIController.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FClassFinder<AAIController> AIControllerRef(TEXT("/Game/PKH/Enemy/BP_EnemyAIController.BP_EnemyAIController_C"));
	if(AIControllerRef.Class)
	{
		AIControllerClass = AIControllerRef.Class;
		AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	}
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	EnemyController = CastChecked<AEnemyAIController>(GetController());
	RunAI();
}

#pragma region AI
void AEnemyBase::RunAI()
{
	EnemyController->RunAI();
}

void AEnemyBase::StopAI()
{
	EnemyController->StopAI();
}
#pragma endregion

#pragma region State
void AEnemyBase::SetState(EEnemyState NewState)
{
	CurState = NewState;
}
#pragma endregion

#pragma region Hp
void AEnemyBase::StaggerOff()
{
	SetState(EEnemyState::Idle);
}

void AEnemyBase::SetHp(int32 NewHp)
{
	CurHp = FMath::Clamp(NewHp, 0, MaxHp);
	if(OnHpChanged.IsBound())
	{
		OnHpChanged.Broadcast(CurHp, MaxHp);
	}

	if(CurHp == 0)
	{
		OnDie();
	}
}

void AEnemyBase::OnDamaged(int32 InDamage, float StaggerTime)
{
	SetState(EEnemyState::Damaged);
	SetHp(CurHp - InDamage);

	// Reset Timer if already timer in active
	if(GetWorldTimerManager().IsTimerActive(StaggerHandle))
	{
		GetWorldTimerManager().ClearTimer(StaggerHandle);
	}
	GetWorldTimerManager().SetTimer(StaggerHandle, this, &AEnemyBase::StaggerOff, StaggerTime, false);
}

void AEnemyBase::OnDie()
{
	SetState(EEnemyState::Die);
}
#pragma endregion
