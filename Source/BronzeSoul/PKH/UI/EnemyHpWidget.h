// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHpWidget.generated.h"

/**
 * 
 */
UCLASS()
class BRONZESOUL_API UEnemyHpWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UEnemyHpWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

// Widgets
protected:
	UPROPERTY(EditDefaultsOnly, meta = ( BindWidget ))
	TObjectPtr<class UProgressBar> ProgressBar_Background;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<class UProgressBar> ProgressBar_EnemyHp;

// Edit Rate
protected:
	UPROPERTY(VisibleAnywhere)
	bool IsEditing = false;

	FTimerHandle HpEditHandle;

	UPROPERTY(EditDefaultsOnly)
	float EditHpDelay = 1.5f;

	UPROPERTY(EditDefaultsOnly)
	float EditHpEps = 0.01f;

	UFUNCTION()
	void StartEditHpRate();

public:
	UFUNCTION()
	void OnHpChanged(int32 CurHp, int32 MaxHp);
};
