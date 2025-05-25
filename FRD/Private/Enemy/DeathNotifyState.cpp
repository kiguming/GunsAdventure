// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/DeathNotifyState.h"
#include "Enemy/EnemyBaseCharacter.h"

void UDeathNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UE_LOG(LogTemp, Log, TEXT("I'm Die Today"));
	/*
	AEnemyBaseCharacter* Enemy = Cast<AEnemyBaseCharacter>(MeshComp->GetOwner());

	if (!Enemy) {
		Enemy->Deleting();
	}
	*/
	//MeshComp->GetOwner()->Destroy();

}
