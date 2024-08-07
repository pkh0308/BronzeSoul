// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Enemy/Mutant/Enemy_Mutant.h"

#include "PKH/Animation/Enemy/MutantAnimInstance.h"

AEnemy_Mutant::AEnemy_Mutant()
{
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

	AnimInstance = CastChecked<UMutantAnimInstance>(GetMesh()->GetAnimInstance());

	// Initialize
	SetEnemyWalk();

}
