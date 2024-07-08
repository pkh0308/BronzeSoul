// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Player/BSPlayerController.h"

ABSPlayerController::ABSPlayerController()
{

}

void ABSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputModeGame();
}

#pragma region InputMode
void ABSPlayerController::SetInputModeGame()
{
	SetInputMode(IM_Game);
	SetShowMouseCursor(false);
}

void ABSPlayerController::SetInputModeUI()
{
	SetInputMode(IM_UI);
	SetShowMouseCursor(true);
}

void ABSPlayerController::SetInputModeBoth()
{
	SetInputMode(IM_Both);
	SetShowMouseCursor(true);
}
#pragma endregion