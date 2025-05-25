// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UI/StatWidget.h"
#include "Player/PlayerCharacter.h"
#include "Components/TextBlock.h"

void UStatWidget::ReloadStats(class APlayerCharacter* Player)
{
	StatDamage->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Player->GetAttackDamage())));
	StatDef->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Player->GetDef())));
	StatSpeed->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Player->GetPlayerSpeed())));
	StatReload->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), Player->GetReloadingSpeed())));
	StatCriChance->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Player->GetCriticalChance() * 100)));
	StatCriDamage->SetText(FText::FromString(FString::Printf(TEXT("%.2f"), Player->GetCriticalDamage())));
}
