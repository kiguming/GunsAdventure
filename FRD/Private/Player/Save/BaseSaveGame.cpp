// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Save/BaseSaveGame.h"

UBaseSaveGame::UBaseSaveGame()
{
    SaveSlotName = TEXT("SaveSlot");
    UserIndex = 0;
    CriDamageGrade = 0;
    CriChanceGrade = 0;
    DefGrade = 0;
    DamageGrade = 0;
    SpeedGrade = 0;
    HealthGrade = 0;
    AmmoGrade = 0;
    ReloadGrade = 0;
    MaxScore = 0;
    Money = 100000;
    UseWeapon = 0;
    BuyAR = false;
    BuySG = false;
    MasterSound = 1.0f;
}
