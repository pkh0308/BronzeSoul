// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Enemy/Mutant/Enemy_Mutant.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "PKH/AI/EnemyAIController.h"
#include "PKH/Animation/Enemy/MutantAnimInstance.h"

AEnemy_Mutant::AEnemy_Mutant()
{
	PrimaryActorTick.bCanEverTick = true;

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
#pragma endregion

#pragma region Jump Attack
bool AEnemy_Mutant::IsWaitingJumpAttack()
{
	return WaitingJumpAttack;
}

void AEnemy_Mutant::BeginJumpAttack()
{
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

void AEnemy_Mutant::EndJumpAttack()
{
	JA_Target = nullptr;
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	OnJumpAttackFinished.ExecuteIfBound();
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