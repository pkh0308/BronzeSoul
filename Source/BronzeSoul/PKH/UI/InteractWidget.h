// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractWidget.generated.h"

/**
 * 
 */
UCLASS()
class BRONZESOUL_API UInteractWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

// Widget
protected:
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<class UTextBlock> Txt_Interact;

public:
	void UpdateText(const FString& NewText) const;
};
