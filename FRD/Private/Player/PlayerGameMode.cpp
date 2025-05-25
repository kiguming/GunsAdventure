// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerGameMode.h"

APlayerGameMode::APlayerGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	KillCount = 0;
}

void APlayerGameMode::BeginPlay()
{
	Super::BeginPlay();

	ElapsedGameTime = 0.0f;
}

void APlayerGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedGameTime += DeltaTime;
	if (FMath::Fmod(ElapsedGameTime, 60.0f) < DeltaTime) // DeltaTime 내에 60의 배수에 해당하는 순간만 실행
	{
		IncreaseRound(); // 60초마다 1라운드씩 증가시킴.
		UE_LOG(LogTemp, Log, TEXT("Time : %f , Round : %d"), ElapsedGameTime, GameRound);
	}
	GameTimeUpdatedEvent.Broadcast(ElapsedGameTime);
}

float APlayerGameMode::GetElapsedGameTime() const
{
	return ElapsedGameTime;
}

void APlayerGameMode::IncreaseKillCount()
{
	KillCount++;
	// 킬 카운트가 업데이트되었음을 브로드캐스트합니다.
	OnKillCountUpdated.Broadcast(KillCount);
}

void APlayerGameMode::IncreaseRound()
{
	GameRound++;

}

