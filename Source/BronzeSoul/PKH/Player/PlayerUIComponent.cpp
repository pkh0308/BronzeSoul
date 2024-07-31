// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Player/PlayerUIComponent.h"

#include "PKH/UI/HealthAndStaminaWidget.h"

// Sets default values for this component's properties
UPlayerUIComponent::UPlayerUIComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	static ConstructorHelpers::FClassFinder<UHealthAndStaminaWidget> HealthAndStaminaUIClassRef(TEXT("/Game/PKH/UI/WBP_HealthAndStamina.WBP_HealthAndStamina_C"));
	if( HealthAndStaminaUIClassRef.Class )
	{
		HealthAndStaminaUIClass = HealthAndStaminaUIClassRef.Class;
	}
}

void UPlayerUIComponent::BeginPlay()
{
	Super::BeginPlay();

	HealthAndStaminaUI = Cast<UHealthAndStaminaWidget>(CreateWidget(GetWorld(), HealthAndStaminaUIClass));
	ensure(HealthAndStaminaUI);
	HealthAndStaminaUI->AddToViewport();
}

TObjectPtr<UHealthAndStaminaWidget> UPlayerUIComponent::GetHealthAndStaminaUI()
{
	return HealthAndStaminaUI;
}
