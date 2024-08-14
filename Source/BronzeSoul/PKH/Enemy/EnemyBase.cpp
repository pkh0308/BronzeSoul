
#include "PKH/Enemy/EnemyBase.h"

#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PKH/CollisionProfiles.h"
#include "PKH/AI/EnemyAIController.h"
#include "PKH/Player/BSPlayerCharacter.h"
#include "PKH/UI/EnemyHpWidget.h"
#include "Runtime/AIModule/Classes/AIController.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	GetCapsuleComponent()->SetCollisionProfileName(COLLISION_ENEMY);

	static ConstructorHelpers::FClassFinder<AAIController> AIControllerRef(TEXT("/Game/PKH/Enemy/BP_EnemyAIController.BP_EnemyAIController_C"));
	if(AIControllerRef.Class)
	{
		AIControllerClass = AIControllerRef.Class;
		AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	}

	HealthUIComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpUI"));
	HealthUIComponent->SetupAttachment(GetCapsuleComponent());
	HealthUIComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthUIComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HealthUIComponent->SetDrawSize(FVector2D(150, 25));
	static ConstructorHelpers::FClassFinder<UEnemyHpWidget> HpUIRef(TEXT("/Game/PKH/UI/BP_EnemyHp.BP_EnemyHp_C"));
	if( HpUIRef.Class )
	{
		HealthUIComponent->SetWidgetClass(HpUIRef.Class);
	}
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	EnemyController = CastChecked<AEnemyAIController>(GetController());
	RunAI();

	// UI
	HealthUIComponent->InitWidget();
	if( UEnemyHpWidget* HpUI = Cast<UEnemyHpWidget>(HealthUIComponent->GetWidget()) )
	{
		OnHpChanged.AddDynamic(HpUI, &UEnemyHpWidget::OnHpChanged);
	}

	// Initialize Stat
	SetHp(MaxHp);
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
	if(false == IsDead())
	{
		SetState(EEnemyState::Idle);
	}
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
	// 무적 여부 검사
	// 피격 후 InvincibleTime만큼 무적 부여
	if(IsInvincible)
	{
		return;
	}
	IsInvincible = true;
	GetWorldTimerManager().SetTimer(InvincibleHandle, this, &AEnemyBase::InvincibleOff, InvincibleTime, false);

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

void AEnemyBase::InvincibleOff()
{
	IsInvincible = false;
}
#pragma endregion

#pragma region Attack
int32 AEnemyBase::GetEnemyAtk() const
{
	return EnemyAtk;
}

void AEnemyBase::Attack()
{
	
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
		if( HealthUIComponent->GetWidget() )
		{
			HealthUIComponent->GetWidget()->SetVisibility(ESlateVisibility::Hidden);
		}
	}), MeshHideDelay, false);
}
#pragma endregion

