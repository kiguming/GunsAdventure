// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "ExpBar.generated.h"

/**
 * 
 */
UCLASS()
class FRD_API UExpBar : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* ExpProgressBar;


	void SetExpProgress(float ExpPer);
};
