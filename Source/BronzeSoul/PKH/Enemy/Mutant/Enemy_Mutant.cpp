// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Enemy/Mutant/Enemy_Mutant.h"

#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PKH/CollisionProfiles.h"
#include "PKH/AI/EnemyAIController.h"
#include "PKH/Animation/Enemy/MutantAnimInstance.h"
#include "PKH/Player/BSPlayerCharacter.h"

AEnemy_Mutant::AEnemy_Mutant()
{
	PrimaryActorTick.bCanEverTick = true;

	// 일반 공격 판정 컴포넌트 추가
	RightAttackColl = CreateDefaultSubobject<UBoxComponent>(TEXT("RightAttackColl"));
	RightAttackColl->SetupAttachment(GetMesh(), TEXT("Socket_RightAttack"));
	RightAttackColl->SetCollisionProfileName(COLLISION_ENEMY_ATTACK);
	RightAttackColl->SetRelativeLocation(FVector(2, -40, 0));
	RightAttackColl->SetBoxExtent(FVector(20, 30, 20));
	RightAttackColl->OnComponentBeginOverlap.AddDynamic(this, &AEnemy_Mutant::NormalAttack);

	LeftAttackColl = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftAttackColl"));
	LeftAttackColl->SetupAttachment(GetMesh(), TEXT("Socket_LeftAttack"));
	LeftAttackColl->SetCollisionProfileName(COLLISION_ENEMY_ATTACK);
	LeftAttackColl->SetRelativeLocation(FVector(-12, -52, 0));
	LeftAttackColl->SetBoxExtent(FVector(30));
	LeftAttackColl->OnComponentBeginOverlap.AddDynamic(this, &AEnemy_Mutant::NormalAttack);
	// 점프 공격 판정 컴포넌트 추가
	JumpAttackColl = CreateDefaultSubobject<UBoxComponent>(TEXT("JumpAttackColl"));
	JumpAttackColl->SetupAttachment(GetMesh(), TEXT("Socket_JumpAttack"));
	JumpAttackColl->SetCollisionProfileName(COLLISION_ENEMY_ATTACK);
	JumpAttackColl->SetRelativeLocation(FVector(0, -14, 76));
	JumpAttackColl->SetBoxExtent(FVector(80, 10, 80));
	JumpAttackColl->OnComponentBeginOverlap.AddDynamic(this, &AEnemy_Mutant::JumpAttack);

	// 메시 위치 조정
	GetMesh()->AddRelativeLocation(FVector(-14, 0, 0));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/PKH/Character/Mutant/Mesh_RootAdded/Mutant.Mutant'"));
	if(MeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRef(TEXT("/Game/PKH/Character/Mutant/Blueprint/ABP_Mutant.ABP_Mutant_C"));
	if(AnimInstanceRef.Class)
	{
		GetMesh()->SetAnimClass(AnimInstanceRef.Class);
	}
}

void AEnemy_Mutant::BeginPlay()
{
	Super::BeginPlay();

	MyAnimInstance = CastChecked<UMutantAnimInstance>(GetMesh()->GetAnimInstance());

	// Initialize
	SetEnemyWalk();
	SetNormalAttackColl(false, true);
	SetNormalAttackColl(false, false);
	SetJumpAttackColl(false);
}

void AEnemy_Mutant::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(WaitingJumpAttack)
	{
		const FVector DirVec = (JA_Target->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		SetActorRotation(DirVec.ToOrientationRotator());
	}
	else if(OnJumpAttack)
	{
		const FVector OriginLoc = GetActorLocation();
		const FVector DeltaMove = FMath::VInterpTo(OriginLoc, JA_TargetLoc, DeltaSeconds, 1);
		SetActorLocation(DeltaMove);
	}
}

#pragma region Attack
void AEnemy_Mutant::Attack()
{
	Super::Attack();

	MyAnimInstance->PlayMontage_Attack();
}

void AEnemy_Mutant::SetNormalAttackColl(bool IsActive, bool IsLeft)
{
	if(IsActive )
	{
		if(IsLeft)
		{
			LeftAttackColl->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
		else
		{
			RightAttackColl->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
	}
	else
	{
		if ( IsLeft )
		{
			LeftAttackColl->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		else
		{
			RightAttackColl->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}

void AEnemy_Mutant::NormalAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABSPlayerCharacter* Player = Cast<ABSPlayerCharacter>(OtherActor);
	if(nullptr == OtherActor)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("[AEnemy_Mutant::NormalAttack] "));
	Player->OnDamaged(20, 400); // 임시값
}
#pragma endregion

#pragma region Jump Attack
void AEnemy_Mutant::JumpAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABSPlayerCharacter* Player = Cast<ABSPlayerCharacter>(OtherActor);
	if ( nullptr == OtherActor )
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("[AEnemy_Mutant::JumpAttack] "));
	Player->OnDamaged(50, 1200); // 임시값
}

bool AEnemy_Mutant::IsWaitingJumpAttack()
{
	return WaitingJumpAttack;
}

void AEnemy_Mutant::BeginJumpAttack()
{
	IsSuperArmor = true;

	JA_Target = EnemyController->GetTargetActor();
	if( JA_Target ) // Target이 nullptr이 아닐때만 점프 공격으로 이행
	{
		WaitingJumpAttack = true;
	}
	GetCharacterMovement()->SetMovementMode(MOVE_Flying);
}

void AEnemy_Mutant::PlayJumpAttackAnim()
{
	WaitingJumpAttack = false;
	MyAnimInstance->PlayMontage_JumpAttack();

	// 위치 계산
	JA_TargetLoc = JA_Target->GetActorLocation();
	JA_TargetDir = (JA_TargetLoc - GetActorLocation()).GetSafeNormal();
}

// 애니메이션에서 점프 뛰는 순간에 호출
// 타겟 방향으로 이동 시작
void AEnemy_Mutant::OnJumpBegin()
{
	OnJumpAttack = true;
}

// 애니메이션에서 점프가 끝나는 순간에 호출
// 타겟 방향으로 이동 중지
void AEnemy_Mutant::OnJumpEnd()
{
	OnJumpAttack = false;
}

void AEnemy_Mutant::SetJumpAttackFinished(FOnJumpAttackFinished NewOnJumpAttackFinished)
{
	OnJumpAttackFinished = NewOnJumpAttackFinished;
}

void AEnemy_Mutant::SetJumpAttackColl(bool IsActive)
{
	if ( IsActive )
	{
		JumpAttackColl->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		JumpAttackColl->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AEnemy_Mutant::EndJumpAttack()
{
	IsSuperArmor = false;

	JA_Target = nullptr;
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	OnJumpAttackFinished.ExecuteIfBound();
}

void AEnemy_Mutant::OnDamaged(int32 InDamage, AActor* Attacker)
{
	Super::OnDamaged(InDamage, Attacker);

	if(false == IsSuperArmor)
	{
		MyAnimInstance->PlayMontage_Damaged();
	}
}
#pragma endregion

#pragma region Die
void AEnemy_Mutant::OnDie()
{
	Super::OnDie();

	MyAnimInstance->PlayMontage_Die();
	WaitingJumpAttack = false;
}
#pragma endregion