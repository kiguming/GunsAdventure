// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BaseSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class FRD_API UBaseSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

    UPROPERTY(VisibleAnywhere, Category = Basic)
    FString PlayerName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    FString SaveSlotName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    uint32 UserIndex;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player stat")
    int CriChanceGrade;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player stat")
    int CriDamageGrade;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player stat")
    int DefGrade;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player stat")
    int DamageGrade;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player stat")
    int SpeedGrade;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player stat")
    int HealthGrade;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player stat")
    int ReloadGrade;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player stat")
    int AmmoGrade;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player stat")
    int MaxScore;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player stat")
    int Money;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player stat")
    int UseWeapon;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player stat")
    bool BuyAR;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player stat")
    bool BuySG;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player stat")
    TArray<bool> BuyList;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    float MasterSound;
    

    UBaseSaveGame();
   

};
