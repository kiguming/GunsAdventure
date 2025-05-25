// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "DeathNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class FRD_API UDeathNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};
