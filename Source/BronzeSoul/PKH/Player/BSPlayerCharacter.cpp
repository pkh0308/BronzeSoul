// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Player/BSPlayerCharacter.h"

// Sets default values
ABSPlayerCharacter::ABSPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABSPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABSPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABSPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

