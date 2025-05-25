// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UI/DamageWidget.h"
#include "Components/TextBlock.h"

void UDamageWidget::ShowDamage(float Damage,bool type)
{
	DamageText->SetText(FText::AsNumber(Damage));

	FLinearColor TextColor;
	if (type) {//크리티컬이라면
		TextColor = FLinearColor(1.0f, 0.0f, 1.0f);//분홍색
	}
	else {//아니라면
		TextColor = FLinearColor(0.0f, 0.0f, 1.0f);//파란색
	}

	DamageText->SetColorAndOpacity(TextColor);
}
