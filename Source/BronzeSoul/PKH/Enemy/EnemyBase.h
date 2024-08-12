#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEnemyHpChanged, int32, CurHp, int32, MaxHp);

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle = 0,
	Attack,
	Damaged,
	Die
};

UCLASS()
class BRONZESOUL_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();

protected:
	virtual void BeginPlay() override;

// Animation
protected:
	UPROPERTY()
	TObjectPtr<class UAnimInstance> AnimInstance;
	
// AI
protected:
	UPROPERTY(VisibleAnywhere, Category="AI")
	TObjectPtr<class AEnemyAIController> EnemyController;

	void RunAI();
	void StopAI();

// State
protected:
	EEnemyState CurState = EEnemyState::Idle;

public:
	void SetState(EEnemyState NewState);

// Hp
protected:
	UPROPERTY(VisibleAnywhere, Category = "Status")
	int32 CurHp = 100;

	UPROPERTY(EditDefaultsOnly, Category = "Status")
	int32 MaxHp = 100;

	FTimerHandle StaggerHandle;

	void StaggerOff();

	void SetHp(int32 NewHp);

	// 피격 시 일정시간 무적 처리
	UPROPERTY(EditDefaultsOnly)
	float InvincibleTime = 0.2f;

	UPROPERTY(VisibleAnywhere)
	bool IsInvincible = false;

	FTimerHandle InvincibleHandle;

	UFUNCTION()
	void InvincibleOff();

public:
	FOnEnemyHpChanged OnHpChanged;

	virtual void OnDamaged(int32 InDamage, float StaggerTime, AActor* Attacker);

// Attack
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Status")
	int32 EnemyAtk;

public:
	int32 GetEnemyAtk() const;

	virtual void Attack();

// Speed
protected:
	UPROPERTY(EditAnywhere)
	float WalkSpeed = 100.0f;

	UPROPERTY(EditAnywhere)
	float RunSpeed = 500.0f;

public:
	void SetEnemyWalk();
	void SetEnemyRun();

// Death
protected:
	UPROPERTY(EditDefaultsOnly)
	float MeshHideDelay = 5.0f;

	FTimerHandle HideMeshHandle;

	virtual void OnDie();

public:
	bool IsDead() const;

	void HideMesh();

// UI
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UWidgetComponent> HealthUIComponent;
};
