// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BSPlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerHealthChanged, int32, CurHp, int32, MaxHp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerStaminaChanged, int32, CurStamina, int32, MaxStamina);

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	Idle = 0,
	Attack,
	Guard,
	Dodge,
	Damaged,
	Die
};

UCLASS()
class BRONZESOUL_API ABSPlayerCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ABSPlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Variables for convenience
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class ABronzeSoulGameMode> GameMode;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class ABSPlayerController> PlayerController;

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

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UStaticMeshComponent> WeaponComp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UStaticMeshComponent> ShieldComp;

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
	TObjectPtr<class UInputAction> IA_Dodge;

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
	void GuardOn(const FInputActionValue& InputAction);

	UFUNCTION()
	void GuardOff(const FInputActionValue& InputAction);

	UFUNCTION()
	void Dodge(const FInputActionValue& InputAction);

// Animation
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<class UPaladinAnimInstance> AnimInstance;

// Direction
protected:
	FVector DirVec;

// Equipment
public:
	void SetWeaponMesh(TObjectPtr<class UStaticMesh> NewWeaponMesh, FTransform NewTransform);
	void SetShieldMesh(TObjectPtr<class UStaticMesh> NewShieldMesh, FTransform NewTransform);

// State
protected:
	EPlayerState CurState = EPlayerState::Idle;

	bool CanMove();
	bool CanAttack();
	bool CanGuardOn();
	bool CanGuardOff();
	bool CanDodge();

	void OnStateChanged_Attack();
	void OnStateChanged_Guard();
	void OnStateChanged_Dodge();
	void OnStateChanged_Die();

public:
	void SetState(EPlayerState NewState);

	FORCEINLINE EPlayerState GetState() const { return CurState; }

// HP
protected:
	UPROPERTY(VisibleAnywhere, Category="Status")
	int32 CurHp;

	UPROPERTY(EditDefaultsOnly, Category = "Status")
	int32 MaxHp = 100;

	FTimerHandle StaggerHandle;

	void SetHp(int32 NewHp);

	void StaggerOff();

public:
	FOnPlayerHealthChanged OnHealthChanged;

	int32 GetCurHp() const;

	void OnDamaged(int32 InDamage, float StaggerTime);

	void OnDie();

// Stamina
protected:
	UPROPERTY(VisibleAnywhere, Category = "Status")
	int32 CurStamina;

	UPROPERTY(EditDefaultsOnly, Category = "Status")
	int32 MaxStamina = 100;

	UPROPERTY(EditAnywhere, Category = "Status")
	int32 DeltaStamina_Recovery = 1;

	UPROPERTY(EditAnywhere, Category = "Status")
	float DeltaTime_StaminaRecovery = 0.2f;

	FTimerHandle StaminaRecoveryHandle;

	UFUNCTION()
	void RestoreStamina();

	void SetStamina(int32 NewStamina);

public:
	FOnPlayerStaminaChanged OnStaminaChanged;

	int32 GetCurStamina() const;

	bool UseStamina(int32 RequiredStamina);

// Attack
protected:
	UPROPERTY(EditDefaultsOnly, Category="Status")
	int32 PlayerAtk;

	UFUNCTION()
	void OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, 
		                      const FHitResult& SweepResult);

	void CancelAttack();

public:
	int32 GetPlayerAtk() const;

	void SetWeaponCollision(bool IsAttacking);

// Guard
protected:
	UPROPERTY(EditAnywhere)
	int32 DeltaStamina_Guard = 1;

	UPROPERTY(EditAnywhere)
	float DeltaTime_Guard = 0.1f;

	FTimerHandle GuardHandle;

	UFUNCTION()
	void OnShieldBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
									  const FHitResult& SweepResult);

public:
	void SetShieldCollision(bool CurGuard);

	bool OnGuardNow() const;

// Dodge
protected:
	UPROPERTY(EditAnywhere)
	int32 DeltaStamina_Dodge = 20;

public:
	void DodgeEnd();

// Die
public:
	bool IsDead();
	void GameOver();

// UI
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UPlayerUIComponent> UIComp;

// IGenericTeamAgentInterface
private:
	int32 TeamID;

public:
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
};
