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
	int32 CurHp;

	UPROPERTY(EditDefaultsOnly, Category = "Status")
	int32 MaxHp;

	FTimerHandle StaggerHandle;

	void StaggerOff();

	void SetHp(int32 NewHp);

public:
	FOnEnemyHpChanged OnHpChanged;

	virtual void OnDamaged(int32 InDamage, float StaggerTime);

	virtual void OnDie();
};
