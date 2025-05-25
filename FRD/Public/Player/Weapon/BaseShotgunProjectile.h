// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/BaseProjectile.h"
#include "BaseShotgunProjectile.generated.h"

/**
 * 
 */
UCLASS()
class FRD_API ABaseShotgunProjectile : public ABaseProjectile
{
	GENERATED_BODY()
	

	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
