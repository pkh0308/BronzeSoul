
#include "PKH/Enemy/EnemyBase.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PKH/AI/EnemyAIController.h"
#include "PKH/Player/BSPlayerCharacter.h"
#include "Runtime/AIModule/Classes/AIController.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

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

	// Test
	FTimerHandle DieHandle;
	GetWorldTimerManager().SetTimer(DieHandle, FTimerDelegate::CreateLambda([this]()
	{
		SetHp(0);
	}), 5.0f, false);
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

void AEnemyBase::OnDamaged(int32 InDamage, float StaggerTime, AActor* Attacker)
{
	SetState(EEnemyState::Damaged);
	SetHp(CurHp - InDamage);

	// Reset Timer if already timer in active
	if(GetWorldTimerManager().IsTimerActive(StaggerHandle))
	{
		GetWorldTimerManager().ClearTimer(StaggerHandle);
	}
	GetWorldTimerManager().SetTimer(StaggerHandle, this, &AEnemyBase::StaggerOff, StaggerTime, false);

	if(Attacker->IsA<ABSPlayerCharacter>())
	{
		EnemyController->SetKey_Player(Attacker);
	}
}
#pragma endregion

#pragma region Attack
int32 AEnemyBase::GetEnemyAtk() const
{
	return EnemyAtk;
}

void AEnemyBase::Attack()
{
	UE_LOG(LogTemp, Log, TEXT("[EnemyBase::Attack] Attack"))
}
#pragma endregion

#pragma region Speed
void AEnemyBase::SetEnemyWalk()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}
 
void AEnemyBase::SetEnemyRun()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}
#pragma endregion

#pragma region Death
void AEnemyBase::OnDie()
{
	SetState(EEnemyState::Die);
	EnemyController->StopAI();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

bool AEnemyBase::IsDead() const
{
	return CurState == EEnemyState::Die;
}

void AEnemyBase::HideMesh()
{
	GetWorldTimerManager().SetTimer(HideMeshHandle, FTimerDelegate::CreateLambda([this]()
	{
		GetMesh()->SetHiddenInGame(true);
	}), MeshHideDelay, false);
}
#pragma endregion

