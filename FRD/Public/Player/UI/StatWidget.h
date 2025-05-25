// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatWidget.generated.h"

/**
 * 
 */
UCLASS()
class FRD_API UStatWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget)) // 공격력 스텟을 읽기위한 텍스트박스
		class UTextBlock* StatDamage;

	UPROPERTY(meta = (BindWidget)) // 방어력 스텟을 읽기위한 텍스트박스
		class UTextBlock* StatDef;

	UPROPERTY(meta = (BindWidget)) // 이동속도 스텟을 읽기위한 텍스트박스
		class UTextBlock* StatSpeed;

	UPROPERTY(meta = (BindWidget)) // 재장전 속도 스텟을 읽기위한 텍스트박스
		class UTextBlock* StatReload;

	UPROPERTY(meta = (BindWidget)) // 이동속도 스텟을 읽기위한 텍스트박스
		class UTextBlock* StatCriChance;

	UPROPERTY(meta = (BindWidget)) // 이동속도 스텟을 읽기위한 텍스트박스
		class UTextBlock* StatCriDamage;

public:
	void ReloadStats(class APlayerCharacter* Player);
};
