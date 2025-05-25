// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UI/ExpBar.h"

void UExpBar::SetExpProgress(float ExpPer)
{
	ExpProgressBar->SetPercent(ExpPer);
}
