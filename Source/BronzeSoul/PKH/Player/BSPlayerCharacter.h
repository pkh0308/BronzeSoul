// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BSPlayerCharacter.generated.h"

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
};
