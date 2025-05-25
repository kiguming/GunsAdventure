// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UI/HpWidget.h"

void UHpWidget::SetHpProgress(float HpPer)
{
	HpProgressBar->SetPercent(HpPer);
}
