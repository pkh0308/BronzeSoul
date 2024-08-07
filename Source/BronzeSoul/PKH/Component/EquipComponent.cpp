
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
	if(false == Player->UseStamina(5))
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
}
#pragma endregion

#pragma region Guard
void UEquipComponent::EquipShield()
{
	HasShield = true;
}

void UEquipComponent::UnequipShield()
{
	HasShield = false;
}

bool UEquipComponent::HasShieldNow()
{
	return HasShield;
}
#pragma endregion
