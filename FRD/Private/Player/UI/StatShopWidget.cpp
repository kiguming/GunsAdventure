// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UI/StatShopWidget.h"
#include "Player/Save/StartGameMode.h"
#include "Player/Save/BaseSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"

void UStatShopWidget::OnHGClicked()
{
	if (UseWeapon != 0) {
		UseWeapon = 0;
		HGText->SetText(FText::FromString(FString::Printf(TEXT("장착중"))));
		if (BuyAR) {//만약 AR을 샀다면
			ARText->SetText(FText::FromString(FString::Printf(TEXT("미장착"))));
		}
		if (BuySG) {//만약 SG를 샀다면
			SGText->SetText(FText::FromString(FString::Printf(TEXT("미장착"))));
		}
		AStartGameMode* GameMode = Cast<AStartGameMode>(GetWorld()->GetAuthGameMode());
		GameMode->SaveGameAll(CriChanceGrade, CriDamageGrade, DefGrade, DamageGrade, SpeedGrade, HealthGrade, ReloadGrade, AmmoGrade, UseWeapon, BuyAR, BuySG, HaveMoney);
	}
	
}

void UStatShopWidget::OnARClicked()
{
	if (BuyAR) {//AR을 산상태
		if (UseWeapon != 1) {
			UseWeapon = 1;
			ARText->SetText(FText::FromString(FString::Printf(TEXT("장착중"))));
			//핸드건은 항상 산상태니까 바꿀 필요없음
			HGText->SetText(FText::FromString(FString::Printf(TEXT("미장착"))));
			if (BuySG) {//만약 샷건을 샀다면
				SGText->SetText(FText::FromString(FString::Printf(TEXT("미장착"))));
			}
			AStartGameMode* GameMode = Cast<AStartGameMode>(GetWorld()->GetAuthGameMode());
			GameMode->SaveGameAll(CriChanceGrade, CriDamageGrade, DefGrade, DamageGrade, SpeedGrade, HealthGrade, ReloadGrade, AmmoGrade, UseWeapon, BuyAR, BuySG, HaveMoney);
		}
	}else { //AR을 사지않은 상태
		if (HaveMoney >= ARPrice) {//AR가격보단 돈이 많아야함
			if (YesNoBox) {
				YesNoBox->SetVisibility(ESlateVisibility::Visible);//확인창을 보이게 함.
				if (YesButton) {
					YesButton->OnClicked.Clear();
					YesButton->OnClicked.AddDynamic(this, &UStatShopWidget::OnBuyARClicked);
				}
				if (NoButton) {
					NoButton->OnClicked.Clear();
					NoButton->OnClicked.AddDynamic(this, &UStatShopWidget::OnCancleClicked);
				}
			}
		}
		
	}
}

void UStatShopWidget::OnSGClicked()
{
	if (BuySG) {//AR을 산상태
		if (UseWeapon != 2) {
			UseWeapon = 2;
			SGText->SetText(FText::FromString(FString::Printf(TEXT("장착중"))));
			//핸드건은 항상 산상태니까 바꿀 필요없음
			HGText->SetText(FText::FromString(FString::Printf(TEXT("미장착"))));
			if (BuyAR) {//만약 라이플을 샀다면
				ARText->SetText(FText::FromString(FString::Printf(TEXT("미장착"))));
			}
			AStartGameMode* GameMode = Cast<AStartGameMode>(GetWorld()->GetAuthGameMode());
			GameMode->SaveGameAll(CriChanceGrade, CriDamageGrade, DefGrade, DamageGrade, SpeedGrade, HealthGrade, ReloadGrade, AmmoGrade, UseWeapon, BuyAR, BuySG, HaveMoney);
		}
	}
	else { //AR을 사지않은 상태
		if (HaveMoney >= SGPrice) {//AR가격보단 돈이 많아야함
			if (YesNoBox) {
				YesNoBox->SetVisibility(ESlateVisibility::Visible);//확인창을 보이게 함.
				if (YesButton) {
					YesButton->OnClicked.Clear();
					YesButton->OnClicked.AddDynamic(this, &UStatShopWidget::OnBuySGClicked);
				}
				if (NoButton) {
					NoButton->OnClicked.Clear();
					NoButton->OnClicked.AddDynamic(this, &UStatShopWidget::OnCancleClicked);
				}
			}
		}
	}
}

void UStatShopWidget::OnBuyARClicked()
{
	YesNoBox->SetVisibility(ESlateVisibility::Hidden);
	HaveMoney -= ARPrice;
	BuyAR = true;
	Moneys->SetText(FText::FromString(FString::Printf(TEXT("%d"), HaveMoney)));
	AStartGameMode* GameMode = Cast<AStartGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->SaveGameAll(CriChanceGrade, CriDamageGrade, DefGrade, DamageGrade, SpeedGrade, HealthGrade, ReloadGrade, AmmoGrade, UseWeapon, BuyAR, BuySG, HaveMoney);
	ARText->SetText(FText::FromString(FString::Printf(TEXT("미장착"))));
}

void UStatShopWidget::OnBuySGClicked()
{
	YesNoBox->SetVisibility(ESlateVisibility::Hidden);
	HaveMoney -= SGPrice;
	BuySG = true;
	Moneys->SetText(FText::FromString(FString::Printf(TEXT("%d"), HaveMoney)));
	AStartGameMode* GameMode = Cast<AStartGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->SaveGameAll(CriChanceGrade, CriDamageGrade, DefGrade, DamageGrade, SpeedGrade, HealthGrade, ReloadGrade, AmmoGrade, UseWeapon, BuyAR, BuySG, HaveMoney);
	SGText->SetText(FText::FromString(FString::Printf(TEXT("미장착"))));
}

void UStatShopWidget::OnCancleClicked()
{
	YesNoBox->SetVisibility(ESlateVisibility::Hidden);//확인창을 안보이게바꿈
}

void UStatShopWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (GetWorld() && GetWorld()->GetAuthGameMode()) {
		AStartGameMode* GameMode = Cast<AStartGameMode>(GetWorld()->GetAuthGameMode());
		GameMode->LoadGame();
		if (GameMode) {
			//무기 버튼관련 처리
			if (HGButton) {
				HGButton->OnClicked.AddDynamic(this, &UStatShopWidget::OnHGClicked);
			}
			if (ARButton) {
				ARButton->OnClicked.AddDynamic(this, &UStatShopWidget::OnARClicked);
			}
			if (SGButton) {
				SGButton->OnClicked.AddDynamic(this, &UStatShopWidget::OnSGClicked);
			}


			if (StatCriChancePlus) {
				StatCriChancePlus->OnClicked.AddDynamic(this, &UStatShopWidget::OnStatCriChancePlusClicked);
			}
			if (StatCriChanceMinus) {
				StatCriChanceMinus->OnClicked.AddDynamic(this, &UStatShopWidget::OnStatCriChanceMinusClicked);
			}


			if (StatCriDamagePlus) {
				StatCriDamagePlus->OnClicked.AddDynamic(this, &UStatShopWidget::OnStatCriDamagePlusClicked);
			}
			if (StatCriDamageMinus) {
				StatCriDamageMinus->OnClicked.AddDynamic(this, &UStatShopWidget::OnStatCriDamageMinusClicked);
			}


			if (StatDefPlus) {
				StatDefPlus->OnClicked.AddDynamic(this, &UStatShopWidget::OnStatDefPlusClicked);
			}
			if (StatDefMinus) {
				StatDefMinus->OnClicked.AddDynamic(this, &UStatShopWidget::OnStatDefMinusClicked);
			}


			if (StatDamagePlus) {
				StatDamagePlus->OnClicked.AddDynamic(this, &UStatShopWidget::OnStatDamagePlusClicked);
			}
			if (StatDamageMinus) {
				StatDamageMinus->OnClicked.AddDynamic(this, &UStatShopWidget::OnStatDamageMinusClicked);
			}


			if (StatSpeedPlus) {
				StatSpeedPlus->OnClicked.AddDynamic(this, &UStatShopWidget::OnStatSpeedPlusClicked);
			}
			if (StatSpeedMinus) {
				StatSpeedMinus->OnClicked.AddDynamic(this, &UStatShopWidget::OnStatSpeedMinusClicked);
			}


			if (StatHealthPlus) {
				StatHealthPlus->OnClicked.AddDynamic(this, &UStatShopWidget::OnStatHealthPlusClicked);
			}
			if (StatHealthMinus) {
				StatHealthMinus->OnClicked.AddDynamic(this, &UStatShopWidget::OnStatHealthMinusClicked);
			}

			if (StatAmmoPlus) {
				StatAmmoPlus->OnClicked.AddDynamic(this, &UStatShopWidget::OnStatAmmoPlusClicked);
			}
			if (StatAmmoMinus) {
				StatAmmoMinus->OnClicked.AddDynamic(this, &UStatShopWidget::OnStatAmmoMinusClicked);
			}


			if (StatReloadPlus) {
				StatReloadPlus->OnClicked.AddDynamic(this, &UStatShopWidget::OnStatReloadPlusClicked);
			}
			if (StatReloadMinus) {
				StatReloadMinus->OnClicked.AddDynamic(this, &UStatShopWidget::OnStatReloadMinusClicked);
			}

			if (ButtonOk) {
				ButtonOk->OnClicked.AddDynamic(this, &UStatShopWidget::OnButtonOkClicked);
			}


			UE_LOG(LogTemp, Log, TEXT("게임모드 불러옴"));
			UBaseSaveGame* LoadGameInstance = GameMode->LoadGameInstance;
			if (LoadGameInstance) {
				UE_LOG(LogTemp, Log, TEXT("로드 데이터 불러옴"));
				if (StatCriChance) {
					StatCriChance->SetText(FText::FromString(FString::Printf(TEXT("%d"), LoadGameInstance->CriChanceGrade)));
				}
				if (StatCriDamage) {
					StatCriDamage->SetText(FText::FromString(FString::Printf(TEXT("%d"), LoadGameInstance->CriDamageGrade)));
				}
				if (StatDef) {
					StatDef->SetText(FText::FromString(FString::Printf(TEXT("%d"), LoadGameInstance->DefGrade)));
				}
				if (StatDamage) {
					StatDamage->SetText(FText::FromString(FString::Printf(TEXT("%d"), LoadGameInstance->DamageGrade)));
				}
				if (StatSpeed) {
					StatSpeed->SetText(FText::FromString(FString::Printf(TEXT("%d"), LoadGameInstance->SpeedGrade)));
				}
				if (StatHealth) {
					StatHealth->SetText(FText::FromString(FString::Printf(TEXT("%d"), LoadGameInstance->HealthGrade)));
				}
				if (StatAmmo) {
					StatAmmo->SetText(FText::FromString(FString::Printf(TEXT("%d"), LoadGameInstance->AmmoGrade)));
				}
				if (StatReload) {
					StatReload->SetText(FText::FromString(FString::Printf(TEXT("%d"), LoadGameInstance->ReloadGrade)));
				}
				if (Moneys) {
					Moneys->SetText(FText::FromString(FString::Printf(TEXT("%dG"), LoadGameInstance->Money)));
					HaveMoney = LoadGameInstance->Money;
				}
				if (StatCriChancePrice) {
					CriChanceGrade = LoadGameInstance->CriChanceGrade;
					StatCriChancePrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (CriChanceGrade * 100))));
				}
				if (StatCriDamagePrice) {
					CriDamageGrade = LoadGameInstance->CriDamageGrade;
					StatCriDamagePrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (CriDamageGrade * 100))));
				}
				if (StatDefPrice) {
					DefGrade = LoadGameInstance->DefGrade;
					StatDefPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (DefGrade * 100))));
				}
				if (StatDamagePrice) {
					DamageGrade = LoadGameInstance->DamageGrade;
					StatDamagePrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (DamageGrade * 100))));
				}
				if (StatSpeedPrice) {
					SpeedGrade = LoadGameInstance->SpeedGrade;
					StatSpeedPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (SpeedGrade * 100))));
				}
				if (StatHealthPrice) {
					HealthGrade = LoadGameInstance->HealthGrade;
					StatHealthPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (HealthGrade * 100))));
				}
				if (StatAmmoPrice) {
					AmmoGrade = LoadGameInstance->AmmoGrade;
					StatAmmoPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (AmmoGrade * 100))));
				}
				if (StatReloadPrice) {
					ReloadGrade = LoadGameInstance->ReloadGrade;
					StatReloadPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (ReloadGrade * 100))));
				}
				UseWeapon = LoadGameInstance->UseWeapon;
				if (HGText) {
					if (UseWeapon == 0) {
						HGText->SetText(FText::FromString(FString::Printf(TEXT("장착중"))));
					}
					else {
						HGText->SetText(FText::FromString(FString::Printf(TEXT("미장착"))));
					}
				}
				if (ARText) {
					BuyAR = LoadGameInstance->BuyAR;
					if (!BuyAR) {//AR을 사지않았다면
						ARText->SetText(FText::FromString(FString::Printf(TEXT("%dG"), ARPrice)));
					}
					else {
						if (UseWeapon == 1) {
							ARText->SetText(FText::FromString(FString::Printf(TEXT("장착중"))));
						}
						else {
							ARText->SetText(FText::FromString(FString::Printf(TEXT("미장착"))));
						}
					}
				}
				if (SGText) {
					BuySG = LoadGameInstance->BuySG;
					if (!BuySG) {//AR을 사지않았다면
						SGText->SetText(FText::FromString(FString::Printf(TEXT("%dG"), SGPrice)));
					}
					else {
						if (UseWeapon == 2) {
							SGText->SetText(FText::FromString(FString::Printf(TEXT("장착중"))));
						}
						else {
							SGText->SetText(FText::FromString(FString::Printf(TEXT("미장착"))));
						}
					}
				}
			}
		}
	}
}

void UStatShopWidget::OnStatCriChancePlusClicked()
{
	if (CriChanceGrade < 10) { //10단계까지 구매가능
		BuyPirces += 100 + (CriChanceGrade * 100);
		CriChanceGrade++;
		StatCriChance->SetText(FText::FromString(FString::Printf(TEXT("%d"), CriChanceGrade)));
		StatCriChancePrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (CriChanceGrade * 100))));
		AllPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), BuyPirces)));
	}
	
}

void UStatShopWidget::OnStatCriChanceMinusClicked()
{
	if (CriChanceGrade > 0) { //0단계까지 판매가능
		CriChanceGrade--;
		BuyPirces -= 100 + (CriChanceGrade * 100);
		StatCriChance->SetText(FText::FromString(FString::Printf(TEXT("%d"), CriChanceGrade)));
		StatCriChancePrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (CriChanceGrade * 100))));
		AllPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), BuyPirces)));
	}
}

void UStatShopWidget::OnStatCriDamagePlusClicked()
{
	if (CriDamageGrade < 10) { //10단계까지 구매가능
		BuyPirces += 100 + (CriDamageGrade * 100);
		CriDamageGrade++;
		StatCriDamage->SetText(FText::FromString(FString::Printf(TEXT("%d"), CriDamageGrade)));
		StatCriDamagePrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (CriDamageGrade * 100))));
		AllPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), BuyPirces)));
	}
}

void UStatShopWidget::OnStatCriDamageMinusClicked()
{
	if (CriDamageGrade > 0) { //0단계까지 판매가능
		CriDamageGrade--;
		BuyPirces -= 100 + (CriDamageGrade * 100);
		StatCriDamage->SetText(FText::FromString(FString::Printf(TEXT("%d"), CriDamageGrade)));
		StatCriDamagePrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (CriDamageGrade * 100))));
		AllPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), BuyPirces)));
	}
}

void UStatShopWidget::OnStatDefPlusClicked()
{
	if (DefGrade <= 10) { //10단계까지 구매가능
		BuyPirces += 100 + (DefGrade * 100);
		DefGrade++;
		StatDef->SetText(FText::FromString(FString::Printf(TEXT("%d"), DefGrade)));
		StatDefPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (DefGrade * 100))));
		AllPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), BuyPirces)));
	}
}

void UStatShopWidget::OnStatDefMinusClicked()
{
	if (DefGrade > 0) { //0단계까지 판매가능
		DefGrade--;
		BuyPirces -= 100 + (DefGrade * 100);
		StatDef->SetText(FText::FromString(FString::Printf(TEXT("%d"), DefGrade)));
		StatDefPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (DefGrade * 100))));
		AllPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), BuyPirces)));
	}
}

void UStatShopWidget::OnStatDamagePlusClicked()
{
	if (DamageGrade <= 10) { //10단계까지 구매가능
		BuyPirces += 100 + (DamageGrade * 100);
		DamageGrade++;
		StatDamage->SetText(FText::FromString(FString::Printf(TEXT("%d"), DamageGrade)));
		StatDamagePrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (DamageGrade * 100))));
		AllPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), BuyPirces)));
	}
}

void UStatShopWidget::OnStatDamageMinusClicked()
{
	if (DamageGrade > 0) { //0단계까지 판매가능
		DamageGrade--;
		BuyPirces -= 100 + (DamageGrade * 100);
		StatDamage->SetText(FText::FromString(FString::Printf(TEXT("%d"), DamageGrade)));
		StatDamagePrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (DamageGrade * 100))));
		AllPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), BuyPirces)));
	}

}

void UStatShopWidget::OnStatSpeedPlusClicked()
{
	if (SpeedGrade <= 10) { //10단계까지 구매가능
		BuyPirces += 100 + (SpeedGrade * 100);
		SpeedGrade++;
		StatSpeed->SetText(FText::FromString(FString::Printf(TEXT("%d"), SpeedGrade)));
		StatSpeedPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (SpeedGrade * 100))));
		AllPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), BuyPirces)));
	}
}

void UStatShopWidget::OnStatSpeedMinusClicked()
{
	if (SpeedGrade > 0) { //0단계까지 판매가능
		SpeedGrade--;
		BuyPirces -= 100 + (SpeedGrade * 100);
		StatSpeed->SetText(FText::FromString(FString::Printf(TEXT("%d"), SpeedGrade)));
		StatSpeedPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (SpeedGrade * 100))));
		AllPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), BuyPirces)));
	}
}

void UStatShopWidget::OnStatHealthPlusClicked()
{
	if (HealthGrade <= 10) { //10단계까지 구매가능
		BuyPirces += 100 + (HealthGrade * 100);
		HealthGrade++;
		StatHealth->SetText(FText::FromString(FString::Printf(TEXT("%d"), HealthGrade)));
		StatHealthPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (HealthGrade * 100))));
		AllPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), BuyPirces)));
	}
}

void UStatShopWidget::OnStatHealthMinusClicked()
{
	if (HealthGrade > 0) { //0단계까지 판매가능
		HealthGrade--;
		BuyPirces -= 100 + (HealthGrade * 100);
		StatHealth->SetText(FText::FromString(FString::Printf(TEXT("%d"), HealthGrade)));
		StatHealthPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (HealthGrade * 100))));
		AllPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), BuyPirces)));
	}
}

void UStatShopWidget::OnStatAmmoPlusClicked()
{
	if (AmmoGrade <= 10) { //10단계까지 구매가능
		BuyPirces += 100 + (AmmoGrade * 100);
		AmmoGrade++;
		StatAmmo->SetText(FText::FromString(FString::Printf(TEXT("%d"), AmmoGrade)));
		StatAmmoPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (AmmoGrade * 100))));
		AllPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), BuyPirces)));
	}
}

void UStatShopWidget::OnStatAmmoMinusClicked()
{
	if (AmmoGrade > 0) { //0단계까지 판매가능
		AmmoGrade--;
		BuyPirces -= 100 + (AmmoGrade * 100);
		StatAmmo->SetText(FText::FromString(FString::Printf(TEXT("%d"), AmmoGrade)));
		StatAmmoPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (AmmoGrade * 100))));
		AllPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), BuyPirces)));
	}
}

void UStatShopWidget::OnStatReloadPlusClicked()
{
	if (ReloadGrade <= 10) { //10단계까지 구매가능
		BuyPirces += 100 + (ReloadGrade * 100);
		ReloadGrade++;
		StatReload->SetText(FText::FromString(FString::Printf(TEXT("%d"), ReloadGrade)));
		StatReloadPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (ReloadGrade * 100))));
		AllPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), BuyPirces)));
	}
}

void UStatShopWidget::OnStatReloadMinusClicked()
{
	if (ReloadGrade > 0) { //0단계까지 판매가능
		ReloadGrade--;
		BuyPirces -= 100 + (ReloadGrade * 100);
		StatReload->SetText(FText::FromString(FString::Printf(TEXT("%d"), ReloadGrade)));
		StatReloadPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), 100 + (ReloadGrade * 100))));
		AllPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), BuyPirces)));
	}
}

void UStatShopWidget::OnButtonOkClicked()
{
	if (HaveMoney >= BuyPirces) {
		HaveMoney -= BuyPirces;
		BuyPirces = 0;
		AStartGameMode* GameMode = Cast<AStartGameMode>(GetWorld()->GetAuthGameMode());
		GameMode->SaveGameAll(CriChanceGrade, CriDamageGrade, DefGrade,DamageGrade, SpeedGrade, HealthGrade, ReloadGrade, AmmoGrade,UseWeapon,BuyAR,BuySG, HaveMoney);
		Moneys->SetText(FText::FromString(FString::Printf(TEXT("%d"), HaveMoney)));
		AllPrice->SetText(FText::FromString(FString::Printf(TEXT("%dG"), BuyPirces)));
	}


	
}
