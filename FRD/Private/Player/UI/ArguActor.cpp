// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UI/ArguActor.h"
#include "Player/PlayerCharacter.h"

// Sets default values
AArguActor::AArguActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AArguActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArguActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AArguActor::SetStat(APlayerCharacter* Player)
{
	
}

