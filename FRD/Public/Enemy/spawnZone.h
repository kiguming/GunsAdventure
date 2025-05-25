// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Enemy/EnemyBaseCharacter.h"
#include "spawnZone.generated.h"

UCLASS()
class FRD_API AspawnZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AspawnZone();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* SpawnComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TSubclassOf<class AEnemyBaseCharacter> EnemyBP;

	FTimerHandle SpawnTimerHandle;

	UWorld* world;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//첫 소환에 소요되는 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Time")
	float FirstSpawnInterval = 0;

	//다음 소환의 유무를 결정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Time")
	bool NextSpawn = true;


	// 소환에 걸리는 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Time")
	float SpawnInterval = 5.0f; 







public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnMob();
};
