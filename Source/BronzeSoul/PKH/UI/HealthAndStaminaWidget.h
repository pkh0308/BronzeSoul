// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthAndStaminaWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedDelegate, int32, CurHealth, int32, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChangedDelegate, int32, CurStamina, int32, MaxStamina);

/**
 * 
 */
UCLASS()
class BRONZESOUL_API UHealthAndStaminaWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

// Widgets
protected:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UProgressBar> ProgressBar_Health;

	UPROPERTY(EditDefaultsOnly, meta = ( BindWidget ))
	TObjectPtr<class UProgressBar> ProgressBar_Stamina;

// For Delegate Binding
protected:
	UFUNCTION()
	void OnHealthChanged(int32 CurHealth, int32 MaxHealth);

	UFUNCTION()
	void OnStaminaChanged(int32 CurStamina, int32 MaxStamina);
};
