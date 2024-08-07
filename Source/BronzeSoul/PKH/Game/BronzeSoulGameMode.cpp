// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Game/BronzeSoulGameMode.h"

#include "PKH/UI/GameOverWidget.h"

ABronzeSoulGameMode::ABronzeSoulGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnRef(TEXT("/Game/PKH/Blueprints/BP_BSPlayerCharacter.BP_BSPlayerCharacter_C"));
	if(DefaultPawnRef.Class)
	{
		DefaultPawnClass = DefaultPawnRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerRef(TEXT("/Game/PKH/Blueprints/BP_BSPlayerController.BP_BSPlayerController_C"));
	if(PlayerControllerRef.Class)
	{
		PlayerControllerClass = PlayerControllerRef.Class;
	}

	// GameOver UI
	static ConstructorHelpers::FClassFinder<UGameOverWidget> GameOverUIClassRef(TEXT("/Game/PKH/UI/WBP_GameOver.WBP_GameOver_C"));
	if ( GameOverUIClassRef.Class )
	{
		GameOverUIClass = GameOverUIClassRef.Class;
	}
}

void ABronzeSoulGameMode::BeginPlay()
{
	Super::BeginPlay();

	if(GameOverUIClass)
	{
		GameOverUI = CreateWidget<UGameOverWidget>(GetWorld(), GameOverUIClass);
		GameOverUI->AddToViewport();
		GameOverUI->SetVisibility(ESlateVisibility::Hidden);
	}
}

#pragma region GameOver
void ABronzeSoulGameMode::GameOver()
{
	GameOverUI->SetVisibility(ESlateVisibility::Visible);
}
#pragma endregion