// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ExpActor.h"
#include "Player/PlayerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AExpActor::AExpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Exps"));
	CollisionComponent->SetCollisionProfileName("ExpDrops");
	SetRootComponent(CollisionComponent);


	ExpDrops = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ExpDrops"));
	ExpDrops->SetCollisionProfileName("ExpDrops");
	ExpDrops->SetupAttachment(CollisionComponent);

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AExpActor::OnOverlapBegin);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AExpActor::OnOverlapEnd);
	points = 1.f;

	
}

// Called when the game starts or when spawned
void AExpActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator RotationToAdd = FRotator(1.0f, 1.0f, 1.0f); // 동전이 x,y,z방향으로 1씩 이동하게끔 만듬.

	// 액터에 회전을 추가
	this->AddActorLocalRotation(RotationToAdd);
}

void AExpActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	UE_LOG(LogTemp, Error, TEXT("OverLapped!!"));
	

	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherComp->GetOwner());
	
	if (Player != nullptr) {
		Player->UpdateExp(points);
		UE_LOG(LogTemp, Error, TEXT("ExpUp!"));
		Destroy();
	}
	
}

void AExpActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

