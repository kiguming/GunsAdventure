// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameTimeUpdated, float, NewTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKillCountUpdated, int32, NewKillCount);


/**
 * 
 */
UCLASS()
class FRD_API APlayerGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	APlayerGameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	float GetElapsedGameTime() const;

	FOnGameTimeUpdated& OnGameTimeUpdated() { return GameTimeUpdatedEvent; }

	FOnKillCountUpdated OnKillCountUpdated;

	// 킬 카운트를 증가시키는 함수
	void IncreaseKillCount();

	void IncreaseRound();
	
	int32 GetRound() const { return GameRound; }

	int32 GetKillCount() {return KillCount;	}

protected:
	float ElapsedGameTime;

	FOnGameTimeUpdated GameTimeUpdatedEvent;
	
	int32 KillCount;

	int32 GameRound;
};
