
#include "PKH/Component/EquipComponent.h"

#include "PKH/Animation/PaladinAnimInstance.h"
#include "PKH/Player/BSPlayerCharacter.h"

UEquipComponent::UEquipComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UEquipComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = CastChecked<ABSPlayerCharacter>(GetOwner());
	AnimInstance = CastChecked<UPaladinAnimInstance>(Player->GetMesh()->GetAnimInstance());
}

#pragma region Attack
void UEquipComponent::Attack()
{
	if(CurCombo == 0 || CanNextCombo)
	{
		DoCombo();
	}
}

void UEquipComponent::DoCombo()
{
	if (CurCombo == MaxCombo)
	{
		return;
	}
	Player->SetState(EPlayerState::Attack);

	DisableCombo();
	AnimInstance->PlayMontage_Combo(++CurCombo);
	UE_LOG(LogTemp, Log, TEXT("[EquipComponent] Combo %d"), CurCombo);
}

void UEquipComponent::EnableCombo()
{
	CanNextCombo = true;
}

void UEquipComponent::DisableCombo()
{
	CanNextCombo = false;
}

void UEquipComponent::ResetCombo()
{
	CanNextCombo = false;
	CurCombo = 0;
	Player->SetState(EPlayerState::Idle);
}
#pragma endregion

#pragma region Guard
void UEquipComponent::Guard()
{
	UE_LOG(LogTemp, Log, TEXT("[EquipComponent] Guard"));

	if(false == HasShield)
	{
		return;
	}


}
#pragma endregion
