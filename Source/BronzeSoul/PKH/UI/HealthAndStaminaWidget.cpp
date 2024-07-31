// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/UI/HealthAndStaminaWidget.h"

#include "Components/ProgressBar.h"
#include "PKH/Player/BSPlayerCharacter.h"

void UHealthAndStaminaWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ABSPlayerCharacter* Player = CastChecked<ABSPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Player->OnHealthChanged.AddDynamic(this, &UHealthAndStaminaWidget::OnHealthChanged);
	Player->OnStaminaChanged.AddDynamic(this, &UHealthAndStaminaWidget::OnStaminaChanged);
}

#pragma region Delegate Binding
void UHealthAndStaminaWidget::OnHealthChanged(int32 CurHealth, int32 MaxHealth)
{
	float HealthRate = static_cast<float>( CurHealth ) / MaxHealth;
	ProgressBar_Health->SetPercent(HealthRate);
}

void UHealthAndStaminaWidget::OnStaminaChanged(int32 CurStamina, int32 MaxStamina)
{
	float StaminaRate = static_cast<float>( CurStamina ) / MaxStamina;
	ProgressBar_Stamina->SetPercent(StaminaRate);
}
#pragma endregion
