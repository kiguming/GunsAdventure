// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/Weapon/WeaponBase.h"
#include "HandGunBase.generated.h"

/**
 * 단발 총의 기본이 되는 클래스
 * 
 */
UCLASS()
class FRD_API AHandGunBase : public AWeaponBase
{
	GENERATED_BODY()

	AHandGunBase();

private:
	

	/** 발사를 시작하는 메서드 */
	virtual void StartFire(APlayerCharacter* Player);


};
