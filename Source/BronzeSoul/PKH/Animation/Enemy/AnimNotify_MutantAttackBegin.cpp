// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Animation/Enemy/AnimNotify_MutantAttackBegin.h"

#include "PKH/Enemy/Mutant/Enemy_Mutant.h"

void UAnimNotify_MutantAttackBegin::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                           const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AEnemy_Mutant* Mutant = Cast<AEnemy_Mutant>(MeshComp->GetOwner());
	if(Mutant)
	{
		Mutant->SetNormalAttackColl(true);
	}
}
