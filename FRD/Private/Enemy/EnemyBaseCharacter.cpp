// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Player/PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/PlayerGameMode.h"
#include "Player/UI/DamageWidget.h"
#include "Enemy/DamageActor.h"

// Sets default values
AEnemyBaseCharacter::AEnemyBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MonsterStats.MaxHealth = 100.0f;

	MonsterStats.Health = MonsterStats.MaxHealth;

	MonsterStats.AttackDamage = 10;
	
	MonsterStats.Def = 0;

	MonsterStats.MonsterSpeed = 800.0f;

	MonsterStats.Exp = 1.0f;

	

	// 스피어를 단순 콜리전 표현으로 사용합니다.
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("UBoxComponent"));
	// 스피어의 콜리전 프로파일 이름을 'Projectile'로 설정합니다.
	BoxComp->BodyInstance.SetCollisionProfileName(TEXT("NoCollision"));
	
	BoxComp->SetupAttachment(RootComponent);

	//콜리전 부딪힐때 반응
	BoxComp->OnComponentHit.AddDynamic(this, &AEnemyBaseCharacter::OnHit);

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBaseCharacter::OnOverlapBegin);

	BoxComp->OnComponentEndOverlap.AddDynamic(this, &AEnemyBaseCharacter::OnOverlapEnd);

	
	
	
	if (DeadAnimation != nullptr) {
		DeadAnimation->bEnableAutoBlendOut = false;
	}
	
}

// Called when the game starts or when spawned
void AEnemyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//몬스터 속도 적용
	GetCharacterMovement()->MaxWalkSpeed = MonsterStats.MonsterSpeed;

}

// Called every frame
void AEnemyBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBaseCharacter::ApplyDamage(float Damage,bool Oncritical, FVector HitLocation, class APlayerCharacter* Player)
{
	Damage *= (100.0 - MonsterStats.Def) / 100.0f;
	MonsterStats.Health -= Damage;

	if (DamageActorClass) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		
		FVector SpawnLocation = HitLocation; // 원하는 위치로 조정
		ADamageActor* DamageActor = GetWorld()->SpawnActor<ADamageActor>(DamageActorClass, SpawnLocation, this->GetActorRotation(), SpawnParams);
		if (DamageActor)
		{
			
			DamageActor->Initialize(Damage, Oncritical);
		}
	}


	UE_LOG(LogTemp, Log, TEXT("남은 체력 %f"), MonsterStats.Health);
	if (ApplySound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ApplySound, this->GetActorLocation());
		
	}

	if (MonsterStats.Health <= 0.0f) {
		Ondead();
		if (Player) {
			Player->UpdateExp(MonsterStats.Exp);
			UE_LOG(LogTemp, Log, TEXT("플레이어 경험치 획득"));
		}
		
	}


}

void AEnemyBaseCharacter::Ondead()
{
	UE_LOG(LogTemp, Log, TEXT("Dead"));
	if (DeadAnimation != nullptr && deading == 0) {
		
		PlayAnimMontage(DeadAnimation);
		deading = 1;
		
		
		if (Moneyclass) // MoneyBP가 유효한지 확인
		{

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			FRotator Rotator;
			FVector SpawnLocation;

			SpawnLocation = GetActorLocation();
			SpawnLocation.Z += 20.0;
			Rotator = GetActorRotation();
			UWorld* world = GetWorld();
			if (world) {
				world->SpawnActor<AMoneyActor>(Moneyclass, SpawnLocation, Rotator, SpawnParams);
			}

		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Enemy Blueprint is not set!"));
		}
		
		GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
		GetMesh()->SetCollisionProfileName("NoCollision");
		
		DetachFromControllerPendingDestroy();
		APlayerGameMode* PlayerGameMode = Cast<APlayerGameMode>(GetWorld()->GetAuthGameMode());

		PlayerGameMode->IncreaseKillCount();

		FTimerManager& TimerManager = GetWorld()->GetTimerManager();

		TimerManager.SetTimer(RemoveTimeHandle, this, &AEnemyBaseCharacter::Deleting, 5.0);
		
	}
	
	
	

	
	
}

void AEnemyBaseCharacter::Attack()
{
	// Try and play a firing animation if specified
	if (AttackAnimation != nullptr)
	{
		
		PlayAnimMontage(AttackAnimation);
		
		
	}
}

void AEnemyBaseCharacter::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
	APlayerCharacter* Player = Cast<APlayerCharacter>(Hit.GetActor());
	UE_LOG(LogTemp, Log, TEXT("Attack Test!"));
	if (Player != nullptr) {
		Player->ApplyDamage(MonsterStats.AttackDamage);
	}
}

void AEnemyBaseCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(SweepResult.GetActor());
	UE_LOG(LogTemp, Log, TEXT("Attack Test!"));
	if (Player != nullptr) {
		Player->ApplyDamage(MonsterStats.AttackDamage);
	}
}

void AEnemyBaseCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AEnemyBaseCharacter::Deleting()
{
	Destroy();
}

