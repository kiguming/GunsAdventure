// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UI/ArgumentBaseWidget.h"
#include "Player/PlayerCharacter.h"
#include "Player/BasePlayerController.h"
#include "Player/Weapon/WeaponBase.h"


UTexture2D* UArgumentBaseWidget::GetImg()
{
	UTexture2D* Texture = Cast<UTexture2D>(Image->GetBrush().GetResourceObject());
	if (Texture != nullptr) {
		return Texture;
	}

	return nullptr;
}

void UArgumentBaseWidget::SetImg(UTexture2D* Texture)
{
	if (Image != nullptr) {
		// 새로운 텍스처를 설정합니다.


		FSlateBrush Brush;

		Brush.SetResourceObject(Texture);

		Image->SetBrush(Brush);

		UE_LOG(LogTemp, Log, TEXT("이미지 변경"));
	}
}

void UArgumentBaseWidget::ClickedButton()
{
	ABasePlayerController* Controller = Cast<ABasePlayerController>(GetOwningPlayer());
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (Player) {
		//증강 처리 부분
		if (Adder.Health != 0.0f) {
			Player->SetMaxHealth(Player->GetMaxHealth() + Adder.Health);
			Player->SetHealth(Player->GetHealth() + Adder.Health);
		}
		if (Adder.AttackDamage != 0.0f) {
			Player->SetAttackDamage(Player->GetAttackDamage() + Adder.AttackDamage);
		}
		if (Adder.PlayerSpeed != 0.0f) {
			Player->SetPlayerSpeed(Player->GetPlayerSpeed() + Adder.PlayerSpeed);
		}
		if (Adder.Def != 0.0f) {
			Player->SetDef(Player->GetDef() +Adder.Def);
		}
		if (Adder.ReloadingSpeed != 0.0f) {
			Player->SetReloadingSpeed(Player->GetReloadingSpeed() + Adder.ReloadingSpeed);
		}
		if (Adder.CriticalChance != 0.0f) {
			Player->SetCriticalChance(Player->GetCriticalChance() + Adder.CriticalChance);
		}
		if (Adder.CriticalDamage != 0.0f) {
			Player->SetCriticalDamage(Player->GetCriticalDamage() + Adder.CriticalDamage);
		}
		if (Adder.addAmmo != 0) {
			
			Player->GetWeapon()->SetAmmoCount(Player->GetWeapon()->GetAmmoCount() + Adder.addAmmo);
		}
		if (Adder.addOn != 0) {
			Player->SetAddOn(Player->GetAddOn() + Adder.addOn);
		}

		UE_LOG(LogTemp, Log, TEXT("Arguments Checked"));
	}
	if (Controller) {
		Controller->ArgumentStop();
	}
	

}

void UArgumentBaseWidget::NativeConstruct()
{
	MyButton->OnClicked.AddDynamic(this, &UArgumentBaseWidget::ClickedButton);
}

