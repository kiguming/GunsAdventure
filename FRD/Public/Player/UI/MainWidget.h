// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HpWidget.h"
#include "ExpBar.h"
#include "MainWidget.generated.h"



/**
 * 
 */
UCLASS()
class FRD_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UHpWidget* HpWidget;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UExpBar* ExpWidget;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UStatWidget* StatWidget;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEscWidget* EscWidget;

	UPROPERTY(meta = (BindWidget)) // UMG에서 위젯을 바인딩하기 위한 매크로
	class UTextBlock* AmmoText;

	UPROPERTY(meta = (BindWidget)) // UMG에서 위젯을 바인딩하기 위한 매크로
	class UTextBlock* TimeText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* KillCountText; // 킬 카운트를 표시할 텍스트 위젯


	UFUNCTION(BlueprintCallable)
	void InitializeHpWidget(UHpWidget* InHpWidget);

	UFUNCTION(BlueprintCallable)
	void InitializeExpWidget(UExpBar* InExpWidget);

	UFUNCTION(BlueprintCallable)
	void UpdateHealth(float NewHealth);

	UFUNCTION(BlueprintCallable)
	void UpdateExp(float NewExp);
	
	void ShowStatBar(class APlayerCharacter* Player);

	void ShowEscMenu();

	UFUNCTION()
	virtual void NativeConstruct() override;

	FString FormatTime(float TimeInSeconds);

	UFUNCTION()
	void UpdateGameTime(float NewTime);

	UFUNCTION()
	void UpdateKillCount(int32 NewKillCount);

	UFUNCTION()
	void UpdateAmmoCount(int AmmoCount, int MaxAmmoCount);

};
