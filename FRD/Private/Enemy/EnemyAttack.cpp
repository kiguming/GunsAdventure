// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAttack.h"
#include "Enemy/EnemyBaseCharacter.h"
#include "Components/BoxComponent.h"


void UEnemyAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	UE_LOG(LogTemp, Log, TEXT("공격시작 "));
	AEnemyBaseCharacter* Enemy = Cast<AEnemyBaseCharacter>(MeshComp->GetOwner());
	if (Enemy != nullptr) {
		Enemy->BoxComp->SetCollisionProfileName("AttackCollision");
	}
}

void UEnemyAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
}

void UEnemyAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UE_LOG(LogTemp, Log, TEXT("공격종료"));
	AEnemyBaseCharacter* Enemy = Cast<AEnemyBaseCharacter>(MeshComp->GetOwner());
	if (Enemy != nullptr) {
		Enemy->BoxComp->SetCollisionProfileName("NoCollision");
	}
}
