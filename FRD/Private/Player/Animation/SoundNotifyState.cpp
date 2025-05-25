// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Animation/SoundNotifyState.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter.h"

void USoundNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(MeshComp->GetOwner());
	
	
}

void USoundNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	
}
