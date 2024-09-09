// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Player/AnimNotify_GuardImpactEnd.h"

#include "BSPlayerCharacter.h"

void UAnimNotify_GuardImpactEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                        const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ABSPlayerCharacter* Player = Cast<ABSPlayerCharacter>(MeshComp->GetOwner());
	if( Player )
	{
		Player->GuardImpactEnd();
	}
}