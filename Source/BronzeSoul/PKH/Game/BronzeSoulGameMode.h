// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BronzeSoulGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BRONZESOUL_API ABronzeSoulGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABronzeSoulGameMode();

protected:
	virtual void BeginPlay() override;

// GameOver
protected:
	UPROPERTY(EditDefaultsOnly, category = "GameOver")
	TSubclassOf<class UGameOverWidget> GameOverUIClass;

	UPROPERTY(EditDefaultsOnly, category = "GameOver")
	TObjectPtr<class UGameOverWidget> GameOverUI;

public:
	void GameOver();
};
