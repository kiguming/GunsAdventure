// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Save/StartGameMode.h"
#include "Player/Save/BaseSaveGame.h"
#include "Kismet/GameplayStatics.h"


void AStartGameMode::BeginPlay()
{
	
}

void AStartGameMode::LoadGame()
{
	//게임 로드 코드
	

	LoadGameInstance = Cast<UBaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UBaseSaveGame::StaticClass()));
	if (LoadGameInstance) {
		LoadGameInstance->SaveSlotName = "MyGames";
		LoadGameInstance->UserIndex = 0;
		LoadGameInstance = Cast<UBaseSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
		UE_LOG(LogTemp, Log, TEXT("게임을 불러옴"));
		if (!LoadGameInstance) {
			LoadGameInstance = NewObject<UBaseSaveGame>();
			UE_LOG(LogTemp, Log, TEXT("불러올게 없다면 새로 만듬"));
			LoadGameInstance->SaveSlotName = "MyGames";
			LoadGameInstance->UserIndex = 0;
			
			UGameplayStatics::SaveGameToSlot(LoadGameInstance, LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex);
		}
	}

}

void AStartGameMode::SaveGameStats(int CriChanceGrade, int CriDamageGrade, int DefGrade, int DamageGrade, int SpeedGrade, int HealthGrade,int ReloadGrade, int AmmoGrade, int Money)
{
	
	FString PlayerName = TEXT("PlayerOne");
	UBaseSaveGame* SaveGameInstance = Cast<UBaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UBaseSaveGame::StaticClass()));
	if (SaveGameInstance) {
		SaveGameInstance->SaveSlotName = "MyGames";
		SaveGameInstance->UserIndex = 0;
		SaveGameInstance->PlayerName = PlayerName;
		SaveGameInstance->CriChanceGrade = CriChanceGrade;
		SaveGameInstance->CriDamageGrade = CriDamageGrade;
		SaveGameInstance->DefGrade = DefGrade;
		SaveGameInstance->DamageGrade = DamageGrade;
		SaveGameInstance->SpeedGrade = SpeedGrade;
		SaveGameInstance->HealthGrade = HealthGrade;
		SaveGameInstance->ReloadGrade = ReloadGrade;
		SaveGameInstance->AmmoGrade = AmmoGrade;


		SaveGameInstance->Money = Money;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
	}
	


}

void AStartGameMode::SaveWeapon(int UseWeapon, bool BuyAR, bool BuySG, int Money)
{
	FString PlayerName = TEXT("PlayerOne");
	UBaseSaveGame* SaveGameInstance = Cast<UBaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UBaseSaveGame::StaticClass()));
	if (SaveGameInstance) {
		SaveGameInstance->SaveSlotName = "MyGames";
		SaveGameInstance->UserIndex = 0;
		SaveGameInstance->PlayerName = PlayerName;
		SaveGameInstance->UseWeapon = UseWeapon;
		SaveGameInstance->BuyAR = BuyAR;
		SaveGameInstance->BuySG = BuySG;
		SaveGameInstance->Money = Money;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
	}
}

void AStartGameMode::SaveGameAll(int CriChanceGrade, int CriDamageGrade, int DefGrade, int DamageGrade, int SpeedGrade, int HealthGrade, int ReloadGrade, int AmmoGrade, int UseWeapon, bool BuyAR, bool BuySG, int Money)
{
	FString PlayerName = TEXT("PlayerOne");
	UBaseSaveGame* SaveGameInstance = Cast<UBaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UBaseSaveGame::StaticClass()));
	if (SaveGameInstance) {

		SaveGameInstance->SaveSlotName = "MyGames";
		SaveGameInstance->UserIndex = 0;
		SaveGameInstance = Cast<UBaseSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex));
		if (SaveGameInstance) {
			SaveGameInstance->SaveSlotName = "MyGames";
			SaveGameInstance->UserIndex = 0;
			SaveGameInstance->PlayerName = PlayerName;
			SaveGameInstance->CriChanceGrade = CriChanceGrade;
			SaveGameInstance->CriDamageGrade = CriDamageGrade;
			SaveGameInstance->DefGrade = DefGrade;
			SaveGameInstance->DamageGrade = DamageGrade;
			SaveGameInstance->SpeedGrade = SpeedGrade;
			SaveGameInstance->HealthGrade = HealthGrade;
			SaveGameInstance->ReloadGrade = ReloadGrade;
			SaveGameInstance->AmmoGrade = AmmoGrade;
			SaveGameInstance->UseWeapon = UseWeapon;
			SaveGameInstance->BuyAR = BuyAR;
			SaveGameInstance->BuySG = BuySG;
			SaveGameInstance->Money = Money;
			UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
		}

		
	}
}

void AStartGameMode::SaveGame()
{
	FString PlayerName = TEXT("PlayerOne");
	UBaseSaveGame* SaveGameInstance = Cast<UBaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UBaseSaveGame::StaticClass()));
	if (SaveGameInstance) {
		SaveGameInstance->SaveSlotName = "MyGames";
		SaveGameInstance->UserIndex = 0;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
		UE_LOG(LogTemp, Log, TEXT("저장함"));
	}
}
