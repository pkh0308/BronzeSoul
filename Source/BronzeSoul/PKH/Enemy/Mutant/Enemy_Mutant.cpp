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

	if(false == DoingJumpAttack)
	{
		return;
	}

	const FVector DirVec = ( Target->GetActorLocation() - GetActorLocation() ).GetSafeNormal();
	SetActorRotation(DirVec.ToOrientationRotator());
}

#pragma region Attack
void AEnemy_Mutant::Attack()
{
	Super::Attack();

	MyAnimInstance->PlayMontage_Attack();
}
#pragma endregion

#pragma region Jump Attack
bool AEnemy_Mutant::IsDoingJumpAttack()
{
	return DoingJumpAttack;
}

void AEnemy_Mutant::BeginJumpAttack()
{
	Target = EnemyController->GetTargetActor();
	if(Target) // Target이 nullptr이 아닐때만 점프 공격으로 이행
	{
		DoingJumpAttack = true;
	}
	GetCharacterMovement()->SetMovementMode(MOVE_Flying);
}

void AEnemy_Mutant::PlayJumpAttackAnim()
{
	MyAnimInstance->PlayMontage_JumpAttack();
}

void AEnemy_Mutant::SetJumpAttackFinished(FOnJumpAttackFinished NewOnJumpAttackFinished)
{
	OnJumpAttackFinished = NewOnJumpAttackFinished;
}

void AEnemy_Mutant::EndJumpAttack()
{
	DoingJumpAttack = false;
	Target = nullptr;
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	OnJumpAttackFinished.ExecuteIfBound();
}
#pragma endregion

#pragma region Die
void AEnemy_Mutant::OnDie()
{
	Super::OnDie();

	MyAnimInstance->PlayMontage_Die();
}
#pragma endregion