// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PaladinAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BRONZESOUL_API UPaladinAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPaladinAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class ABSPlayerCharacter> Player;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCharacterMovementComponent> MoveComp;

// Flags
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bIsIdle : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bIsWalking : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bIsRunning : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bOnGuard : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bIsDead : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WalkThreshold = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RunThreshold = 250;

// Montages
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> AM_ComboMontageOneHand;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> AM_Dodge;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> AM_Guard;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> AM_Damaged;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> AM_KnockDown;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> AM_StandUp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> AM_Die;

public:
	void PlayMontage_Combo(int32 Idx);

	void PlayMontage_Dodge();

	void PlayMontage_Guard();

	void PlayMontage_Damaged();

	void PlayMontage_KnockDown();

	void PlayMontage_StandUp();

	void PlayMontage_Die();

// Texts
protected:
	// Guard
	UPROPERTY(EditDefaultsOnly)
	FName GuardOff = TEXT("GuardOff");

	// Damaged
	UPROPERTY(EditDefaultsOnly)
	TArray<FName> DamagedSections;

};
