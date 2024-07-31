// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerUIComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BRONZESOUL_API UPlayerUIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerUIComponent();

protected:
	virtual void BeginPlay() override;

// Widgets
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHealthAndStaminaWidget> HealthAndStaminaUIClass;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UHealthAndStaminaWidget> HealthAndStaminaUI;

public:	
	TObjectPtr<class UHealthAndStaminaWidget> GetHealthAndStaminaUI();
		
};
