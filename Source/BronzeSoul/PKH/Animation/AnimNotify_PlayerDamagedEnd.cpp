﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Animation/AnimNotify_PlayerDamagedEnd.h"

#include "PKH/Player/BSPlayerCharacter.h"

void UAnimNotify_PlayerDamagedEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
										  const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ABSPlayerCharacter* Player = Cast<ABSPlayerCharacter>(MeshComp->GetOwner());
	if ( Player )
	{
		Player->OnDamagedEnd();
	}
}