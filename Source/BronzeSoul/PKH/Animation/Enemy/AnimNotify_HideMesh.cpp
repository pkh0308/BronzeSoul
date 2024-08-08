// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Animation/Enemy/AnimNotify_HideMesh.h"

#include "PKH/Enemy/EnemyBase.h"

void UAnimNotify_HideMesh::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                  const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AEnemyBase* Enemy = Cast<AEnemyBase>(MeshComp->GetOwner());
	if(Enemy)
	{
		Enemy->HideMesh();
	}
}