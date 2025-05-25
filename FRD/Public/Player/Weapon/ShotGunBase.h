// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/Weapon/WeaponBase.h"
#include "ShotGunBase.generated.h"

/**
 * 
 */
UCLASS()
class FRD_API AShotGunBase : public AWeaponBase
{
	GENERATED_BODY()

	AShotGunBase();
	
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))//한발에 나가는 샷건 탄알의 양
	int ShotgunGage = 7;

	/** 발사를 시작하는 메서드 */
	virtual void StartFire(APlayerCharacter* Player);

public:
	int GetShotgunGage();

};
