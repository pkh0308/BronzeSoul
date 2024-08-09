// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BSGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

	int32 Id;
	int32 AttackValue;
	int32 StaminaCost;

	UPROPERTY()
	TObjectPtr<class UStaticMesh> Mesh;

	FTransform RelativeTransform;
};

USTRUCT(BlueprintType)
struct FShieldData
{
	GENERATED_BODY()

	int32 Id;
	int32 DefenceValue;
	int32 StaminaCost;

	UPROPERTY()
	TObjectPtr<class UStaticMesh> Mesh;

	FTransform RelativeTransform;
};

/**
 * 
 */
UCLASS()
class BRONZESOUL_API UBSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UBSGameInstance();

protected:
	virtual void Init() override;

// Equipment
protected:
	UPROPERTY(VisibleAnywhere, Category="Equipment")
	TMap<int32, FWeaponData> WeaponDataMap;

	UPROPERTY(VisibleAnywhere, Category = "Equipment")
	TMap<int32, FShieldData> ShieldDataMap;

public:
	FWeaponData GetWeaponData(int32 WeaponId);
	FShieldData GetShieldData(int32 ShieldId);
	
};
