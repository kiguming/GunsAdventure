// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UI/GameEndWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Player/BasePlayerController.h"
#include "Player/PlayerGameMode.h"

void UGameEndWidget::ClickedButton()
{
	UE_LOG(LogTemp, Log, TEXT("레벨 옮기기"));
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("startLavel"), true);
}

void UGameEndWidget::NativeConstruct()
{
	ABasePlayerController* PController = Cast<ABasePlayerController>(GetOwningPlayer());
	APlayerGameMode* PGameMode = Cast< APlayerGameMode>(GetWorld()->GetAuthGameMode());

	if (PController&& PGameMode) {
		int32 Minutes = FMath::FloorToInt(PGameMode->GetElapsedGameTime() / 60);
		int32 Seconds = FMath::FloorToInt(FMath::Fmod(PGameMode->GetElapsedGameTime(), 60));
		LevelText->SetText(FText::FromString(FString::Printf(TEXT("획득한 증강의 수 : %d"), PController->GetLevel())));
		EndTimeText->SetText(FText::FromString(FString::Printf(TEXT("생존시간 :%2d : %02d "), Minutes, Seconds)));
		Score = PGameMode->GetKillCount() * 10 + PGameMode->GetElapsedGameTime() * 2 + KillBoss * 500;
		ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score : %d"), Score)));
	}
	else {
		LevelText->SetText(FText::FromString(FString::Printf(TEXT("오류 발생"))));
		EndTimeText->SetText(FText::FromString(FString::Printf(TEXT("오류 발생"))));
	}
	
	QuitButton->OnClicked.AddDynamic(this, &UGameEndWidget::ClickedButton);
}

void UGameEndWidget::VisibleNewScore()
{
	NewRecordText->SetVisibility(ESlateVisibility::Visible);

}
