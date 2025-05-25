// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageWidget.generated.h"

/**
 * 
 */
UCLASS()
class FRD_API UDamageWidget : public UUserWidget
{
	GENERATED_BODY()
	
	

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* DamageText;

	UFUNCTION()
	void ShowDamage(float Damage,bool type);


};
