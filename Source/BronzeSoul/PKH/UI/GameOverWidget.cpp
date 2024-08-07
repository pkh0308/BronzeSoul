// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/UI/GameOverWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Restart->OnClicked.AddDynamic(this, &UGameOverWidget::OnClicked_Restart);
	Btn_Exit->OnClicked.AddDynamic(this, &UGameOverWidget::OnClicked_Exit);
	OnVisibilityChanged.AddDynamic(this, &UGameOverWidget::OnVisible);
}

#pragma region For Bind
void UGameOverWidget::OnClicked_Restart()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Proto"));
}

void UGameOverWidget::OnClicked_Exit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}

void UGameOverWidget::OnVisible(ESlateVisibility InVisibility)
{
	UE_LOG(LogTemp, Log, TEXT("OnVisible"));
	if(InVisibility == ESlateVisibility::Visible)
	{
		PlayAnimation(Anim_GameOver); UE_LOG(LogTemp, Log, TEXT("OnVisible Success"));
	}
}
#pragma endregion
