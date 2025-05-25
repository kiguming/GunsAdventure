// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UI/ArguList/ChangeAmmoArgument.h"
#include "Player/PlayerCharacter.h"
#include "Player/BasePlayerController.h"
#include "Player/BaseProjectile.h"
#include "Player/Weapon/WeaponBase.h"

void UChangeAmmoArgument::ClickedButton()
{
	ABasePlayerController* Controller = Cast<ABasePlayerController>(GetOwningPlayer());
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (Player) {
		if (Player->GetWeapon()->GetProjectile() == ProjectileClass) {//같은 프로젝타일일때는 그냥 공격력 1.2배 올려줌.
			Player->SetAttackDamage(Player->GetAttackDamage() * 1.2);
		}
		else {
			Player->GetWeapon()->SetProjectile(ProjectileClass);
		}
		
		
	}
	if (Controller) {
		Controller->ArgumentStop();
	}
}
