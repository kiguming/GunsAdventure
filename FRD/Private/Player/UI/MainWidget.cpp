// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UI/MainWidget.h"
#include "Player/PlayerGameMode.h"
#include "Components/TextBlock.h"
#include "Player/UI/StatWidget.h"
#include "Player/PlayerCharacter.h"
#include "Player/UI/EscWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"

void UMainWidget::InitializeHpWidget(UHpWidget* InHpWidget)
{
	HpWidget = InHpWidget;
}

void UMainWidget::InitializeExpWidget(UExpBar* InExpWidget)
{
	ExpWidget = InExpWidget;
}


void UMainWidget::UpdateHealth(float NewHealth)
{
	if (HpWidget)
	{
		HpWidget->SetHpProgress(NewHealth);
	}
	
}

void UMainWidget::UpdateExp(float NewExp)
{
	if (ExpWidget) {
		ExpWidget->SetExpProgress(NewExp);
	}
}

void UMainWidget::ShowStatBar(class APlayerCharacter* Player)
{
	if (StatWidget) { //스텟위젯이 있는지 확인
		if (StatWidget->IsVisible()) { //만약 스텟바가 보인다면
			StatWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		else {
			StatWidget->SetVisibility(ESlateVisibility::Visible);
			StatWidget->ReloadStats(Player);
		}
	}
	
}

void UMainWidget::ShowEscMenu()
{
	if (EscWidget->IsVisible()) {//만약 ESC화면이 보인다면.
		EscWidget->SetVisibility(ESlateVisibility::Hidden); //안보이게하고
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		FInputModeGameOnly InputMode;
		GetOwningPlayer()->SetInputMode(InputMode);
		GetOwningPlayer()->bShowMouseCursor = false;
		//게임 다시 진행
		//입력모드도 바꿈
	}
	else {
		EscWidget->SetVisibility(ESlateVisibility::Visible);
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		FInputModeUIOnly InputMode;
		GetOwningPlayer()->SetInputMode(InputMode);
		GetOwningPlayer()->bShowMouseCursor = true;
	}
	
}

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (GetWorld())
	{
		APlayerGameMode* PlayerGameMode = Cast<APlayerGameMode>(GetWorld()->GetAuthGameMode());
		if (PlayerGameMode)
		{
			// OnGameTimeUpdated 델리게이트 추가
			PlayerGameMode->OnGameTimeUpdated().AddDynamic(this, &UMainWidget::UpdateGameTime);
			PlayerGameMode->OnKillCountUpdated.AddDynamic(this, &UMainWidget::UpdateKillCount);

		}
	}
	
}

FString UMainWidget::FormatTime(float TimeInSeconds)
{
	
	int32 Minutes = FMath::FloorToInt(TimeInSeconds / 60);
	int32 Seconds = FMath::FloorToInt(FMath::Fmod(TimeInSeconds, 60));
	FString TimeString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
	return TimeString;
	
}

void UMainWidget::UpdateGameTime(float NewTime)
{
	FString FormattedTime = FormatTime(NewTime);
	TimeText->SetText(FText::FromString(FormattedTime));
}

void UMainWidget::UpdateKillCount(int32 NewKillCount)
{
	// 받아온 킬 카운트를 텍스트로 변환하여 킬 카운트 텍스트 위젯에 표시합니다.
	if (KillCountText)
	{
		KillCountText->SetText(FText::FromString(FString::Printf(TEXT("%d"), NewKillCount)));
	}
}

void UMainWidget::UpdateAmmoCount(int AmmoCount, int MaxAmmoCount)
{
	if (AmmoText) {
		AmmoText->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), AmmoCount, MaxAmmoCount)));
	}
	
	
}

