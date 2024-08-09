// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PKH/Game/BSGameInstance.h"
#include "EquipComponent.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None = 0,
	OneHand,
	TwoHand
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BRONZESOUL_API UEquipComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEquipComponent();

protected:
	virtual void BeginPlay() override;

// Player
protected:
	UPROPERTY(VisibleAnywhere, Category="Player")
	TObjectPtr<class ABSPlayerCharacter> Player;

	UPROPERTY(VisibleAnywhere, Category = "Player")
	TObjectPtr<class UPaladinAnimInstance> AnimInstance;

	EWeaponType CurWeapon = EWeaponType::None;

// Cur Equipment
protected:
	UPROPERTY(EditDefaultsOnly, category="Default")
	int32 DefaultWeaponId = 1001;

	UPROPERTY(EditDefaultsOnly, category = "Default")
	int32 DefaultShieldId = 2001;

	UPROPERTY(VisibleAnywhere)
	FWeaponData CurWeaponData;

	UPROPERTY(VisibleAnywhere)
	FShieldData CurShieldData;

	void Equip(int32 NewId);
	void EquipWeapon(int32 NewWeaponId);
	void EquipShield(int32 NewShieldId);

public:
	int32 GetWeaponAttackValue() const;
	int32 GetShieldDefenceValue() const;

// Attack
protected:
	bool CanNextCombo = false;

	UPROPERTY(VisibleAnywhere, Category="Attack")
	int32 CurCombo = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	int32 MaxCombo = 3;

	void DoCombo();

public:
	void Attack();

	void EnableCombo();
	void DisableCombo();
	void ResetCombo();

// Guard
protected:
	bool HasShield = false;

public:
	void EquipShield();
	void UnequipShield();

	bool HasShieldNow();

		
};
