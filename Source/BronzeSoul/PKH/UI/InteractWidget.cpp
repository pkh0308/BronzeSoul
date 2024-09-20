// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/UI/InteractWidget.h"

#include "Components/TextBlock.h"

void UInteractWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

void UInteractWidget::UpdateText(const FString& NewText) const
{
	Txt_Interact->SetText(FText::FromString(NewText));
}
