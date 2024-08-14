// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/UI/EnemyHpWidget.h"

#include "Components/ProgressBar.h"

UEnemyHpWidget::UEnemyHpWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UEnemyHpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ProgressBar_Background->SetPercent(1.0f);
	ProgressBar_EnemyHp->SetPercent(1.0f);
}

void UEnemyHpWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(IsEditing)
	{
		const float CurRate = ProgressBar_Background->GetPercent();
		const float TargetRate = ProgressBar_EnemyHp->GetPercent();
		const float NextRate = FMath::FInterpConstantTo(CurRate, TargetRate, InDeltaTime, 0.3f);
		ProgressBar_Background->SetPercent(NextRate);

		if(NextRate - TargetRate < EditHpEps)
		{
			IsEditing = false;
		}
	}
}

#pragma region Edit Hp
void UEnemyHpWidget::OnHpChanged(int32 CurHp, int32 MaxHp)
{
	const float HpRate = static_cast<float>(CurHp) / MaxHp;
	ProgressBar_EnemyHp->SetPercent(HpRate);
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	// 이미 체력바 수정 중이라면 종료
	if(IsEditing)
	{
		return;
	}
	
	if(TimerManager.IsTimerActive(HpEditHandle))
	{
		TimerManager.ClearTimer(HpEditHandle);
	}
	TimerManager.SetTimer(HpEditHandle, this, &UEnemyHpWidget::StartEditHpRate, EditHpDelay, false);
}

void UEnemyHpWidget::StartEditHpRate()
{
	IsEditing = true;
}
#pragma endregion