// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BSPlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerHpChanged, int32, CurHp, int32, MaxHp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerStaminaChanged, int32, CurStamina, int32, MaxStamina);

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	Idle = 0,
	Attack,
	Guard,
	Damaged,
	Die
};

UCLASS()
class BRONZESOUL_API ABSPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABSPlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Component
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UCapsuleComponent> CapsuleComp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UCharacterMovementComponent> MoveComp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class USpringArmComponent> SpringArmComp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UCameraComponent> CameraComp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UEquipComponent> EquipComp;


// Input
protected:
	// Mapping Context
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputAction> IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputAction> IA_Look;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputAction> IA_Jump;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputAction> IA_Attack;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputAction> IA_Guard;

	// Functions
	UFUNCTION()
	void Move(const FInputActionValue& InputAction);

	UFUNCTION()
	void Look(const FInputActionValue& InputAction);

	UFUNCTION()
	void Attack(const FInputActionValue& InputAction);

	UFUNCTION()
	void Guard(const FInputActionValue& InputAction);

// Animation
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<class UAnimInstance> AnimInstance;

// State
protected:
	EPlayerState CurState = EPlayerState::Idle;

	bool CanMove();
	bool CanAttack();

public:
	void SetState(EPlayerState NewState);

	FORCEINLINE EPlayerState GetState() const { return CurState; }

// HP
protected:
	UPROPERTY(VisibleAnywhere, Category="Status")
	int32 CurHp;

	UPROPERTY(EditDefaultsOnly, Category = "Status")
	int32 MaxHp;

	FTimerHandle StaggerHandle;

	void SetHp(int32 NewHp);

	void StaggerOff();

public:
	FOnPlayerHpChanged OnHpChanged;

	int32 GetCurHp() const;

	void OnDamaged(int32 InDamage, float StaggerTime);

	void OnDie();

// Stamina
protected:
	UPROPERTY(VisibleAnywhere, Category = "Status")
	int32 CurStamina;

	UPROPERTY(EditDefaultsOnly, Category = "Status")
	int32 MaxStamina;

	void SetStamina(int32 NewStamina);

public:
	FOnPlayerStaminaChanged OnStaminaChanged;

	int32 GetCurStamina() const;

// Attack
protected:
	UPROPERTY(EditDefaultsOnly, Category="Status")
	int32 PlayerAtk;

public:
	int32 GetPlayerAtk() const;
};
