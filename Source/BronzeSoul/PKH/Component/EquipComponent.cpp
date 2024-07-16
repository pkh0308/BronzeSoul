
#include "PKH/Component/EquipComponent.h"

#include "PKH/Player/BSPlayerCharacter.h"

UEquipComponent::UEquipComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UEquipComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = CastChecked<ABSPlayerCharacter>(GetOwner());
	AnimInstance = CastChecked<UAnimInstance>(Player->GetMesh()->GetAnimInstance());
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

	++CurCombo;
	DisableCombo();
	UE_LOG(LogTemp, Log, TEXT("[EquipComponent] Combo %d"), CurCombo);

	FTimerManager& TimeManager = GetWorld()->GetTimerManager();

	if(TimeManager.IsTimerActive(DisableHandle))
	{
		TimeManager.ClearTimer(DisableHandle);
	}

	if(CurCombo < MaxCombo)
	{
		TimeManager.SetTimer(EnableHandle, this, &UEquipComponent::EnableCombo, 1.0f, false);
	}
	TimeManager.SetTimer(DisableHandle, this, &UEquipComponent::ResetCombo, 2.0f, false);
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
void UEquipComponent::Guard()
{
	UE_LOG(LogTemp, Log, TEXT("[EquipComponent] Guard"));

	if(false == HasShield)
	{
		return;
	}


}
#pragma endregion
