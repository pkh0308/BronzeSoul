// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BRONZESOUL_API ABSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABSPlayerController();

protected:
	virtual void BeginPlay() override;

// InputMode
protected:
	FInputModeGameOnly IM_Game;
	FInputModeUIOnly IM_UI;
	FInputModeGameAndUI IM_Both;

public:
	void SetInputModeGame();
	void SetInputModeUI();
	void SetInputModeBoth();
};
