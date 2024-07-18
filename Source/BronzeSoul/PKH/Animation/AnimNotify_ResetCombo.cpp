// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Animation/AnimNotify_ResetCombo.h"

#include "PKH/Component/EquipComponent.h"
#include "PKH/Player/BSPlayerCharacter.h"

void UAnimNotify_ResetCombo::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                    const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ABSPlayerCharacter* Player = Cast<ABSPlayerCharacter>(MeshComp->GetOwner());
	if (nullptr == Player)
	{
		return;
	}

	UEquipComponent* EquipComp = Cast<UEquipComponent>(Player->GetComponentByClass(UEquipComponent::StaticClass()));
	if (nullptr == EquipComp)
	{
		return;
	}

	EquipComp->ResetCombo();
}
