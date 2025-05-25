// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayScreenController.generated.h"

/**
 * 
 */
UCLASS()
class FRD_API APlayScreenController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ChangeResolution(FIntPoint NewResolution);
};