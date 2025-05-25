// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameEndWidget.generated.h"

/**
 * 
 */
UCLASS()
class FRD_API UGameEndWidget : public UUserWidget
{
	GENERATED_BODY()
protected:


	UPROPERTY(meta = (BindWidget)) // UMG에서 위젯을 바인딩하기 위한 매크로
		class UTextBlock* LevelText;

	UPROPERTY(meta = (BindWidget)) // UMG에서 위젯을 바인딩하기 위한 매크로
		class UTextBlock* EndTimeText;

	UPROPERTY(meta = (BindWidget)) // UMG에서 위젯을 바인딩하기 위한 매크로
		class UTextBlock* ScoreText;

	UPROPERTY(meta = (BindWidget)) // UMG에서 위젯을 바인딩하기 위한 매크로
		class UTextBlock* NewRecordText;



	int32 Score;

	int KillBoss = 0;

	UPROPERTY(meta = (BindWidget)) // UMG에서 위젯을 바인딩하기 위한 매크로
		class UButton* QuitButton;
	UFUNCTION()
	void ClickedButton();
	
	void NativeConstruct();

public:

	UFUNCTION()
	int32 GetScore() { return Score; }

	void VisibleNewScore();

};
