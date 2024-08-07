// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class BRONZESOUL_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

// Widgets
protected:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UButton> Btn_Restart;

	UPROPERTY(EditDefaultsOnly, meta = ( BindWidget ))
	TObjectPtr<class UButton> Btn_Exit;

	UPROPERTY(EditDefaultsOnly, meta = ( BindWidgetAnim ), Transient)
	TObjectPtr<class UWidgetAnimation> Anim_GameOver;

// For Bind
protected:
	UFUNCTION()
	void OnClicked_Restart();

	UFUNCTION()
	void OnClicked_Exit();

	UFUNCTION()
	void OnVisible(ESlateVisibility InVisibility);
};
