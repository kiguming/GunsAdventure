// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatShopWidget.generated.h"

/**
 * 
 */
UCLASS()
class FRD_API UStatShopWidget : public UUserWidget
{
	GENERATED_BODY()

	//상점 스텟 등급
	int CriChanceGrade = 0;
	int CriDamageGrade = 0;
	int DefGrade = 0;
	int DamageGrade = 0;
	int SpeedGrade = 0;
	int HealthGrade = 0;
	int AmmoGrade = 0;
	int ReloadGrade = 0;
	int HaveMoney;
	int BuyPirces = 0;
	int ARPrice = 1000;
	int SGPrice = 2000;

	int UseWeapon = 0;//사용하는 무기 0. 핸드건 1. 라이플 2. 샷건
	bool BuyAR = false;
	bool BuySG = false;
public:

	UPROPERTY(meta = (BindWidget)) // 치명확률 스텟 수치
		class UTextBlock* StatCriChance;

	UPROPERTY(meta = (BindWidget)) // 치명확률 플러스 버튼
		class UButton* StatCriChancePlus;

	UPROPERTY(meta = (BindWidget)) // 치명확률 마이너스 버튼
		class UButton* StatCriChanceMinus;

	UPROPERTY(meta = (BindWidget)) // 치명확률 스텟 가격
		class UTextBlock* StatCriChancePrice;

	UPROPERTY(meta = (BindWidget)) // 치명데미지 스텟 수치
		class UTextBlock* StatCriDamage;

	UPROPERTY(meta = (BindWidget)) // 치명데미지 플러스 버튼
		class UButton* StatCriDamagePlus;

	UPROPERTY(meta = (BindWidget)) // 치명데미지 마이너스 버튼
		class UButton* StatCriDamageMinus;

	UPROPERTY(meta = (BindWidget)) // 치명확률 스텟 가격
		class UTextBlock* StatCriDamagePrice;

	UPROPERTY(meta = (BindWidget)) // 방어력 스텟을 읽기위한 텍스트박스
		class UTextBlock* StatDef;

	UPROPERTY(meta = (BindWidget)) // 방어력 플러스 버튼
		class UButton* StatDefPlus;

	UPROPERTY(meta = (BindWidget)) // 방어력 마이너스 버튼
		class UButton* StatDefMinus;

	UPROPERTY(meta = (BindWidget)) // 치명확률 스텟 가격
		class UTextBlock* StatDefPrice;

	UPROPERTY(meta = (BindWidget)) // 공격력 스텟을 읽기위한 텍스트박스
		class UTextBlock* StatDamage;

	UPROPERTY(meta = (BindWidget)) // 공격력 플러스 버튼
		class UButton* StatDamagePlus;

	UPROPERTY(meta = (BindWidget)) // 공격력 마이너스 버튼
		class UButton* StatDamageMinus;

	UPROPERTY(meta = (BindWidget)) // 치명확률 스텟 가격
		class UTextBlock* StatDamagePrice;

	UPROPERTY(meta = (BindWidget)) // 이동속도 스텟을 읽기위한 텍스트박스
		class UTextBlock* StatSpeed;

	UPROPERTY(meta = (BindWidget)) // 속도 플러스 버튼
		class UButton* StatSpeedPlus;

	UPROPERTY(meta = (BindWidget)) // 속도 마이너스 버튼
		class UButton* StatSpeedMinus;

	UPROPERTY(meta = (BindWidget)) // 치명확률 스텟 가격
		class UTextBlock* StatSpeedPrice;

	UPROPERTY(meta = (BindWidget)) // 체력 스텟을 읽기위한 텍스트박스
		class UTextBlock* StatHealth;

	UPROPERTY(meta = (BindWidget)) // 체력 플러스 버튼
		class UButton* StatHealthPlus;

	UPROPERTY(meta = (BindWidget)) // 체력 마이너스 버튼
		class UButton* StatHealthMinus;
	
	UPROPERTY(meta = (BindWidget)) //체력 스텟 가격
		class UTextBlock* StatHealthPrice;

	UPROPERTY(meta = (BindWidget)) // 총알 갯수 스텟을 읽기위한 텍스트박스
		class UTextBlock* StatAmmo;

	UPROPERTY(meta = (BindWidget)) // 총알 플러스 버튼
		class UButton* StatAmmoPlus;

	UPROPERTY(meta = (BindWidget)) // 총알 마이너스 버튼
		class UButton* StatAmmoMinus;

	UPROPERTY(meta = (BindWidget)) // 치명확률 스텟 가격
		class UTextBlock* StatAmmoPrice;

	UPROPERTY(meta = (BindWidget)) // 재장전 속도 스텟을 읽기위한 텍스트박스
		class UTextBlock* StatReload;

	UPROPERTY(meta = (BindWidget)) // 재장전 플러스 버튼
		class UButton* StatReloadPlus;

	UPROPERTY(meta = (BindWidget)) // 재장전 마이너스 버튼
		class UButton* StatReloadMinus;

	UPROPERTY(meta = (BindWidget)) // 재장전 마이너스 버튼
		class UTextBlock* StatReloadPrice;

	UPROPERTY(meta = (BindWidget)) // 스텟 구매 적용 버튼
		class UButton* ButtonOk;

	UPROPERTY(meta = (BindWidget)) // 전체 가격 텍스트 표기 텍스트
		class UTextBlock* AllPrice;


	UPROPERTY(meta = (BindWidget)) // 권총 적용 버튼
		class UButton* HGButton;

	UPROPERTY(meta = (BindWidget)) // 권총 텍스트
		class UTextBlock* HGText;

	UPROPERTY(meta = (BindWidget)) // 라이플 적용 버튼
		class UButton* ARButton;

	UPROPERTY(meta = (BindWidget)) // 라이플 텍스트
		class UTextBlock* ARText;

	UPROPERTY(meta = (BindWidget)) // 라이플 적용 버튼
		class UButton* SGButton;

	UPROPERTY(meta = (BindWidget)) // 라이플 텍스트
		class UTextBlock* SGText;
	
	UPROPERTY(meta = (BindWidget)) // 판매 적용 버튼
		class UCanvasPanel* YesNoBox;

	UPROPERTY(meta = (BindWidget)) // 판매 적용 버튼
		class UButton* YesButton;

	UPROPERTY(meta = (BindWidget)) // 판매 적용 버튼
		class UButton* NoButton;

	UPROPERTY(meta = (BindWidget)) // 가진 돈을 확인하는 텍스트
		class UTextBlock* Moneys;

	UFUNCTION()
	void OnHGClicked();

	UFUNCTION()
	void OnARClicked();

	UFUNCTION()
	void OnSGClicked();

	UFUNCTION()
	void OnBuyARClicked();

	UFUNCTION()
	void OnBuySGClicked();

	UFUNCTION()
	void OnCancleClicked();

	UFUNCTION()
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnStatCriChancePlusClicked();

	UFUNCTION()
	void OnStatCriChanceMinusClicked();

	UFUNCTION()
	void OnStatCriDamagePlusClicked();

	UFUNCTION()
	void OnStatCriDamageMinusClicked();

	UFUNCTION()
	void OnStatDefPlusClicked();
	UFUNCTION()
	void OnStatDefMinusClicked();

	UFUNCTION()
	void OnStatDamagePlusClicked();
	UFUNCTION()
	void OnStatDamageMinusClicked();

	UFUNCTION()
	void OnStatSpeedPlusClicked();
	UFUNCTION()
	void OnStatSpeedMinusClicked();

	UFUNCTION()
	void OnStatHealthPlusClicked();
	UFUNCTION()
	void OnStatHealthMinusClicked();

	UFUNCTION()
	void OnStatAmmoPlusClicked();
	UFUNCTION()
	void OnStatAmmoMinusClicked();

	UFUNCTION()
	void OnStatReloadPlusClicked();
	UFUNCTION()
	void OnStatReloadMinusClicked();

	UFUNCTION()
	void OnButtonOkClicked();

};
