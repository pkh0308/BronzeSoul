// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Game/BronzeSoulGameMode.h"

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
}
