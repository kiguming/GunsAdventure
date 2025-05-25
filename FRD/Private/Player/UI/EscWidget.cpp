// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UI/EscWidget.h"
#include "Components/ComboBoxString.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameUserSettings.h"
#include "Components/Slider.h"
#include "Player/BasePlayerController.h"
#include "Player/Save/BaseSaveGame.h"
#include "Kismet/GameplayStatics.h"

void UEscWidget::NativeConstruct()
{
	Super::NativeConstruct();

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

	if (ResolutionComboBox)
	{
		// 여기에 원하는 해상도를 추가합니다.
		ResolutionComboBox->AddOption(TEXT("1920x1080"));
		ResolutionComboBox->AddOption(TEXT("1280x720"));
		ResolutionComboBox->AddOption(TEXT("2560x1440"));
		// 원하는 만큼 해상도를 추가할 수 있습니다.
	}

	if (EscButton) {
		EscButton->OnClicked.AddDynamic(this, &UEscWidget::OnClickEsc);
	}
	if (ReturnButton) {
		ReturnButton->OnClicked.AddDynamic(this, &UEscWidget::OnClickReturn);
	}


	if (ScreenOkButton) {
		ScreenOkButton->OnClicked.AddDynamic(this, &UEscWidget::OnchangeScreen);
	}
	
	
	
}


void UEscWidget::OnchangeScreen()
{
	if (GEngine && GEngine->GameUserSettings)
	{
		// 해상도 변경
		FString SelectedResolution = ResolutionComboBox->GetSelectedOption();
		FIntPoint ScreenRes;
		ScreenRes.X = FCString::Atoi(*SelectedResolution.Left(SelectedResolution.Find("x")));
		ScreenRes.Y = FCString::Atoi(*SelectedResolution.RightChop(SelectedResolution.Find("x") + 1));

		// 전체 화면 모드 변경
		bool bIsFullScreen = FullScreenCheck->IsChecked();

		// 설정 적용
		GEngine->GameUserSettings->SetScreenResolution(ScreenRes);
		GEngine->GameUserSettings->SetFullscreenMode(bIsFullScreen ? EWindowMode::Fullscreen : EWindowMode::Windowed);
		GEngine->GameUserSettings->ApplySettings(false);
	}
}

void UEscWidget::OnClickEsc()
{
	
	FString LevelName = TEXT("StartLevel");

	// 시작 화면으로 이동합니다.
	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName));
}

void UEscWidget::OnClickReturn()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	FInputModeGameOnly InputMode;
	GetOwningPlayer()->SetInputMode(InputMode);
	GetOwningPlayer()->bShowMouseCursor = false;
}

void UEscWidget::ChangeSound(float Value)
{
	UE_LOG(LogTemp, Log, TEXT("벨류변환성공"));
	ABasePlayerController* PController = Cast<ABasePlayerController>(GetOwningPlayer());

	if (PController) {
		UE_LOG(LogTemp, Log, TEXT("사운드 변환됨"));


	}

}


