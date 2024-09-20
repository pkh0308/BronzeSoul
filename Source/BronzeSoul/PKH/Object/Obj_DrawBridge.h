// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PKH/Interface/Interactive.h"
#include "Obj_DrawBridge.generated.h"

UENUM(BlueprintType)
enum class EBridgeState : uint8
{
	Up = 0,
	Down
};

UCLASS()
class BRONZESOUL_API AObj_DrawBridge : public AActor, public IInteractive
{
	GENERATED_BODY()
	
public:	
	AObj_DrawBridge();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

// Component
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UBoxComponent> BoxComp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UStaticMeshComponent> MeshComp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UBoxComponent> DetectComp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UWidgetComponent> UIComp;

	UFUNCTION()
	void OnDetectPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, 
						const FHitResult& SweepResult);

	UFUNCTION()
	void OnLostPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

// for interact
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInteractWidget> InteractUI;

	UPROPERTY(EditAnywhere)
	FRotator UpRotation = FRotator(0, 0, 0);

	UPROPERTY(EditAnywhere)
	FRotator DownRotation = FRotator(-90, 0, 0);

	UPROPERTY(VisibleAnywhere)
	bool IsDrawing = false;

	UPROPERTY(VisibleAnywhere)
	bool IsNearPlayer = false;

	UPROPERTY(EditAnywhere)
	float DrawSpeed = 1.0f;

	UPROPERTY(EditAnywhere)
	float Threshold_DrawRotation = 0.1f;

	EBridgeState CurState = EBridgeState::Up;

	void DrawComplete();

// Interface
public:
	virtual void Interact() override;
};
