// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/UI/ArgumentBaseWidget.h"
#include "ChangeAmmoArgument.generated.h"

/**
 * 
 */
UCLASS()
class FRD_API UChangeAmmoArgument : public UArgumentBaseWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ABaseProjectile> ProjectileClass;

	virtual void ClickedButton() override;

};
