// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UI/PlayScreenController.h"
#include "GameFramework/GameUserSettings.h"

void APlayScreenController::ChangeResolution(FIntPoint NewResolution)
{
    // 게임 설정을 가져옴
    UGameUserSettings* GameSettings = UGameUserSettings::GetGameUserSettings();
    if (GameSettings)
    {
        // 해상도 및 창 모드 변경
        GameSettings->SetScreenResolution(NewResolution);
        GameSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
        GameSettings->ApplySettings(true);
    }
}
