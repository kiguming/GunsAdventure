// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/MoneyActor.h"
#include "Player/PlayerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AMoneyActor::AMoneyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Moneys"));
	CollisionComponent->SetCollisionProfileName("MoneyDrops");
	SetRootComponent(CollisionComponent);


	MoneyDrops = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MoneyDrops"));
	MoneyDrops->SetCollisionProfileName("MoneyDrops");
	MoneyDrops->SetupAttachment(CollisionComponent);

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AMoneyActor::OnOverlapBegin);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AMoneyActor::OnOverlapEnd);
	points = 1.f;
}

// Called when the game starts or when spawned
void AMoneyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMoneyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator RotationToAdd = FRotator(1.0f, 1.0f, 1.0f); // 동전이 x,y,z방향으로 1씩 이동하게끔 만듬.

	// 액터에 회전을 추가
	this->AddActorLocalRotation(RotationToAdd);
}

void AMoneyActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	


	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherComp->GetOwner());

	if (Player != nullptr) {
		Player->UpdateMoney(points);
		UE_LOG(LogTemp, Log, TEXT("돈을 머것엉!"));
		Destroy();
	}
}

void AMoneyActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

