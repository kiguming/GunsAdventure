// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BasePlayerController.h"
#include "Player/UI/MainWidget.h"
#include "Player/UI/UserArgument.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter.h"
#include "Player/UI/ArgumentBaseWidget.h"
#include <algorithm>
#include "Player/UI/ArguActor.h"
#include "Player/Save/BaseSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Player/UI/ArguShopWidget.h"
#include "Player/PlayerGameMode.h"
#include "Player/Weapon/WeaponBase.h"


ABasePlayerController::ABasePlayerController()
{
    PlayerLevel = 0;
    

    
}

void ABasePlayerController::changeHp(float percent)
{
	//HpWidget->UpdateHealth(percent);
}

void ABasePlayerController::Ondead()
{
    APlayerCharacter* player = Cast<APlayerCharacter>(GetPawn());
    if (player) {
        player->DeathEvent();
        FInputModeUIOnly InputMode;
        SetInputMode(InputMode);
    }

    if (DeathSound) {
        UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetSpawnLocation());
    }


    FTimerManager& TimerManager = GetWorld()->GetTimerManager();
    
    TimerManager.SetTimer(DeadTimerHandler, this, &ABasePlayerController::OndeadAfter, 5.0f);
    
}

void ABasePlayerController::OndeadAfter()
{
    UGameplayStatics::SetGamePaused(GetWorld(), true);

    if (GameEndWidgetClass) {
        GameEndWidgetInstance = CreateWidget<UGameEndWidget>(this, GameEndWidgetClass);

        if (GameEndWidgetInstance) {
            GameEndWidgetInstance->AddToViewport();
            bShowMouseCursor = true;
            UBaseSaveGame* SaveLoadGameInstance = Cast<UBaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UBaseSaveGame::StaticClass()));
            if (SaveLoadGameInstance) {
                SaveLoadGameInstance->SaveSlotName = "MyGames";
                SaveLoadGameInstance->UserIndex = 0;
                SaveLoadGameInstance = Cast<UBaseSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveLoadGameInstance->SaveSlotName, SaveLoadGameInstance->UserIndex));
                UE_LOG(LogTemp, Log, TEXT("게임을 불러옴"));
                if (SaveLoadGameInstance) {//저장된 게임이 있다면
                    APlayerCharacter* player = Cast<APlayerCharacter>(GetPawn());
                    if (Player) {
                        UE_LOG(LogTemp, Log, TEXT("플레이어 불러옴"));
                        SaveLoadGameInstance->Money += player->GetMoney();
                        player->DetachFromControllerPendingDestroy();
                        if (GameEndWidgetInstance->GetScore() > SaveLoadGameInstance->MaxScore) {
                            GameEndWidgetInstance->VisibleNewScore();
                            SaveLoadGameInstance->MaxScore = GameEndWidgetInstance->GetScore();
                        }
                    }
                    UGameplayStatics::SaveGameToSlot(SaveLoadGameInstance, SaveLoadGameInstance->SaveSlotName, SaveLoadGameInstance->UserIndex);
                }
                else {//만약에 저장된 게임이 없다면
                    SaveLoadGameInstance = NewObject<UBaseSaveGame>();
                    APlayerCharacter* player = Cast<APlayerCharacter>(GetPawn());
                    if (Player) {
                        UE_LOG(LogTemp, Log, TEXT("플레이어 불러옴"));
                        SaveLoadGameInstance->SaveSlotName = "MyGames";
                        SaveLoadGameInstance->UserIndex = 0;
                        SaveLoadGameInstance->Money = player->GetMoney();
                        SaveLoadGameInstance->MaxScore = GameEndWidgetInstance->GetScore();
                        player->DetachFromControllerPendingDestroy();
                        UGameplayStatics::SaveGameToSlot(SaveLoadGameInstance, SaveLoadGameInstance->SaveSlotName, SaveLoadGameInstance->UserIndex);
                    }
                   

                }

                
            }
        }
    }

}





void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
    APlayerGameMode* GameMode = Cast<APlayerGameMode>(GetWorld()->GetAuthGameMode());
    if (!GameMode) {
        //메인메뉴라서 UI만들어줄 필요없음.
    }
    else {
        //인게임이라서 UI만들어줘야함.
        if (MainWidgetClass)
        {
            // MainWidget 인스턴스를 생성하고 추가합니다.
            MainWidgetInstance = CreateWidget<UMainWidget>(this, MainWidgetClass);

            // MainWidget를 화면에 추가합니다.
            if (MainWidgetInstance)
            {

                MainWidgetInstance->AddToViewport();
                MainWidgetInstance->UpdateHealth(100.0f);
                MainWidgetInstance->UpdateExp(0.0f);
                UpdateLevel();
            }
        }
    }
    

    UBaseSaveGame* SaveLoadGameInstance = Cast<UBaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UBaseSaveGame::StaticClass()));
    if (SaveLoadGameInstance) {
        SaveLoadGameInstance->SaveSlotName = "MyGames";
        SaveLoadGameInstance->UserIndex = 0;
        SaveLoadGameInstance = Cast<UBaseSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveLoadGameInstance->SaveSlotName, SaveLoadGameInstance->UserIndex));
    }

    

    if (SaveLoadGameInstance) { //저장되어있는 정보가 있을경우에는
        if (Argushop.GetDefaultObject()) {//상점이 정의되어있을때
            UE_LOG(LogTemp, Log, TEXT("상점 증강 넘어감"));
            if (SaveLoadGameInstance->BuyList.Num() > 0) { //산 증강이 1개라도 있을때 처리
                for (int32 i = 0; i < Argushop.GetDefaultObject()->GetShopArgu().Num(); i++) {
                    if (SaveLoadGameInstance->BuyList[i]) {//증강이 구매되어있을 경우에만
                        Argument_Lists.Add(Argushop.GetDefaultObject()->GetShopArgu()[i]);//구매한 증강을 리스트에 넣음
                    }
                }
            }
            
        }
    }

    

    
	
}

void ABasePlayerController::ShuffleArray(TArray<TSubclassOf<UArgumentBaseWidget>>& Array)
{
    for (int32 Index = Array.Num() - 1; Index > 0; --Index)
    {
        int32 RandomIndex = FMath::RandRange(0, Index);
        if (Index != RandomIndex)
        {
            Array.Swap(Index, RandomIndex);
        }
    }
}



void ABasePlayerController::ArgumentStart()
{
    
    // 게임 일시 정지
    UGameplayStatics::SetGamePaused(GetWorld(), true);
   

    ShuffleArray(Argument_Lists);//배열을 한번 섞습니다.
   
    // 유저 인터페이스를 생성하고 표시합니다.
    if (LevelUpWidgetClass)
    {
        LevelUpWidgetInstance = CreateWidget<UUserArgument>(this, LevelUpWidgetClass);
        if (LevelUpWidgetInstance)
        {
            UpdateLevel();
            LevelUpWidgetInstance->AddToViewport();
            FInputModeUIOnly InputMode;
            SetInputMode(InputMode);
            bShowMouseCursor = true;
            
            
            
        }
    }
}

void ABasePlayerController::ArgumentStop()
{
    // 유저 인터페이스를 제거합니다.
    if (LevelUpWidgetInstance)
    {
        bShowMouseCursor = false;
        FInputModeGameOnly InputMode;
        SetInputMode(InputMode);
        LevelUpWidgetInstance->RemoveFromParent();
    }
    // 게임을 다시 시작합니다.
   
    UGameplayStatics::SetGamePaused(GetWorld(), false);
    APlayerCharacter* player = Cast<APlayerCharacter>(GetOwner());
    if (player) {
        AWeaponBase* Weapon = Cast<AWeaponBase>(player->GetWeapon());
        if (Weapon) {
            Weapon->StopFire(player);
        }
    }
}

void ABasePlayerController::UpdateLevel()
{
    PlayerLevel++;
}
