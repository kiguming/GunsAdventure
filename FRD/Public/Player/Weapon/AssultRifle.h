// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/Weapon/WeaponBase.h"
#include "AssultRifle.generated.h"


/**
 * 연속발사 총의 기본이 되는 베이스.
 * 
 */
UCLASS()
class FRD_API AAssultRifle : public AWeaponBase
{
	GENERATED_BODY()

	AAssultRifle();

private:
	FTimerHandle FireTimerHandle;

	virtual void BeginPlay();

	/** 발사를 시작하는 메서드 */
	virtual void StartFire(APlayerCharacter* Player);

	/** 발사를 멈추는 메서드*/
	virtual void StopFire(APlayerCharacter* Player) override;

	/** 재장전 메서드*/
	virtual void Reloading(APlayerCharacter* Player) override;

	

	virtual void GoFire(APlayerCharacter* Character);

	virtual void ChangeAuto() override;
public:
	virtual void EndReload(APlayerCharacter* Player) override;
};
