
#include "PKH/Component/EquipComponent.h"

#include "PKH/Animation/PaladinAnimInstance.h"
#include "PKH/Game/BSGameInstance.h"
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

	// Initialize
	Equip(DefaultWeaponId);
	Equip(DefaultShieldId);
}

#pragma region Equip
void UEquipComponent::Equip(int32 NewEquipmentId)
{
	if ( NewEquipmentId > 1000 && NewEquipmentId < 2000 )
	{
		EquipWeapon(NewEquipmentId);
	}
	else if ( NewEquipmentId > 2000 && NewEquipmentId < 3000 )
	{
		EquipShield(NewEquipmentId);
	}
}

void UEquipComponent::EquipWeapon(int32 NewWeaponId)
{
	UBSGameInstance* GI = CastChecked<UBSGameInstance>(GetWorld()->GetGameInstance());

	CurWeaponData = GI->GetWeaponData(NewWeaponId);
	Player->SetWeaponMesh(CurWeaponData.Mesh, CurWeaponData.RelativeTransform);
}

void UEquipComponent::EquipShield(int32 NewShieldId)
{
	UBSGameInstance* GI = CastChecked<UBSGameInstance>(GetWorld()->GetGameInstance());

	CurShieldData = GI->GetShieldData(NewShieldId);
	Player->SetShieldMesh(CurShieldData.Mesh, CurShieldData.RelativeTransform);
}

int32 UEquipComponent::GetWeaponAttackValue() const
{
	return CurWeaponData.AttackValue;
}

int32 UEquipComponent::GetShieldDefenceValue() const
{
	return CurShieldData.DefenceValue;
}
#pragma endregion

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
	// 마지막 콤보중이라면 공격 불가
	if (CurCombo == MaxCombo)
	{
		return;
	}
	// 스태미나가 부족하면 공격 불가
	if(false == Player->UseStamina(CurWeaponData.StaminaCost))
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
