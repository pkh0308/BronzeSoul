// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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
	bool HasShieldNow();

		
};
