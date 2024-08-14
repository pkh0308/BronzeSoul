// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Game/BSGameInstance.h"

UBSGameInstance::UBSGameInstance()
{
	// Weapon
	FWeaponData Weapon_1001;
	Weapon_1001.Id = 1001;
	Weapon_1001.AttackValue = 10;
	Weapon_1001.StaminaCost = 10;
	Weapon_1001.RelativeTransform.SetLocation(FVector(50.00f, -6.34f, 11.18f));
	Weapon_1001.RelativeTransform.SetRotation(FQuat(FRotator(161.56f, 87.64f, 79.92f)));
	Weapon_1001.RelativeTransform.SetScale3D(FVector(0.7f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh_1001Ref(TEXT("/Script/Engine.StaticMesh'/Game/PKH/Weapon/OneHand/Worn_Sword_FBX.Worn_Sword_FBX'"));
	if ( Mesh_1001Ref.Object )
	{
		Weapon_1001.Mesh = Mesh_1001Ref.Object;
	}
	WeaponDataMap.Add(Weapon_1001.Id, Weapon_1001);

	// Shield
	FShieldData Shield_2001;
	Shield_2001.Id = 2001;
	Shield_2001.DefenceValue = 10;
	Shield_2001.StaminaCost = 10;
	Shield_2001.RelativeTransform.SetLocation(FVector(0, -7.49f, -2.51f));
	Shield_2001.RelativeTransform.SetRotation(FQuat(FRotator(15, -90, -90))); 
	Shield_2001.RelativeTransform.SetScale3D(FVector(0.2f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh_2001Ref(TEXT("/Script/Engine.StaticMesh'/Game/PKH/Shield/WoodShield/Viking_shield.Viking_shield'"));
	if ( Mesh_2001Ref.Object )
	{
		Shield_2001.Mesh = Mesh_2001Ref.Object;
	}
	ShieldDataMap.Add(Shield_2001.Id, Shield_2001);
}

void UBSGameInstance::Init()
{
	Super::Init();
}

#pragma region Equipment
FWeaponData UBSGameInstance::GetWeaponData(int32 WeaponId)
{
	return WeaponDataMap.Contains(WeaponId) ? WeaponDataMap[WeaponId] : FWeaponData();
}

FShieldData UBSGameInstance::GetShieldData(int32 ShieldId)
{
	return ShieldDataMap.Contains(ShieldId) ? ShieldDataMap[ShieldId] : FShieldData();
}
#pragma endregion