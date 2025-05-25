// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StartGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FRD_API AStartGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	void LoadGame();

	class UBaseSaveGame* LoadGameInstance;

	void SaveGameStats(int CriChanceGrade, int CriDamageGrade, int DefGrade, int DamageGrade, int SpeedGrade, int HealthGrade, int ReloadGrade, int AmmoGrade, int Money);

	void SaveWeapon(int UseWeapon, bool BuyAR, bool BuySG, int Money);

	void SaveGameAll(int CriChanceGrade, int CriDamageGrade, int DefGrade, int DamageGrade, int SpeedGrade, int HealthGrade, int ReloadGrade, int AmmoGrade, int UseWeapon, bool BuyAR, bool BuySG, int Money);

	void SaveGame();
};
