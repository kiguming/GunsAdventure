// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HpWidget.generated.h"

/**
 * 
 */
UCLASS()
class FRD_API UHpWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* HpProgressBar;


	void SetHpProgress(float HpPer);
};
