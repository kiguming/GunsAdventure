// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/spawnZone.h"
#include "Components/BoxComponent.h"
#include "Enemy/EnemyBaseCharacter.h"
#include "TimerManager.h"
#include "Player/PlayerGameMode.h"

// Sets default values
AspawnZone::AspawnZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 스피어를 단순 콜리전 표현으로 사용합니다.
	SpawnComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("USpawnComponent"));
	SpawnComponent->SetupAttachment(RootComponent);

	

	

}

// Called when the game starts or when spawned
void AspawnZone::BeginPlay()
{
	Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("스포너확인"));
    // 타이머 매니저를 가져옵니다.
    FTimerManager& TimerManager = GetWorld()->GetTimerManager();
     
    TimerManager.SetTimer(SpawnTimerHandle, this, &AspawnZone::SpawnMob, SpawnInterval, NextSpawn, FirstSpawnInterval);

  
}

// Called every frame
void AspawnZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    


}

void AspawnZone::SpawnMob()
{
    UE_LOG(LogTemp, Log, TEXT("SpawnEnemy"));
    if (EnemyBP) // EnemyBP가 유효한지 확인
    {
        FVector BoxSize = SpawnComponent->GetScaledBoxExtent();
        
        float RandomX = FMath::FRandRange(0.0, BoxSize.X);
        float RandomY = FMath::FRandRange(0.0, BoxSize.Y);

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        FRotator Rotator;
        FVector SpawnLocation;
        
        SpawnLocation.Set(RandomX, RandomY, 0);
        SpawnLocation += GetActorLocation();
        Rotator = GetActorRotation();
        world = GetWorld();
        if (world) {
            world->SpawnActor<AEnemyBaseCharacter>(EnemyBP, SpawnLocation, Rotator, SpawnParams);
        }
        
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Enemy Blueprint is not set!"));
    }
}

