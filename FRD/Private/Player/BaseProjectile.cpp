// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BaseProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Enemy/EnemyBaseCharacter.h"
#include "Player/PlayerCharacter.h"
#include "Math/UnrealMathUtility.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}

	if (!CollisionComponent)
	{
		// 스피어를 단순 콜리전 표현으로 사용합니다.
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// 스피어의 콜리전 프로파일 이름을 'Projectile'로 설정합니다.
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
		// 스피어의 콜리전 반경을 설정합니다.
		CollisionComponent->InitSphereRadius(15.0f);
		//콜리전 부딪힐때 반응
		CollisionComponent->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHit);
		// 루트 컴포넌트가 콜리전 컴포넌트가 되도록 설정합니다.
		RootComponent = CollisionComponent;
	}

	if (!ProjectileMovementComponent)
	{
		// 이 컴포넌트를 사용하여 이 발사체의 이동을 주도합니다.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 3000.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = false;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	if (!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		
		ProjectileMeshComponent->SetupAttachment(RootComponent);
	}
	
	InitialLifeSpan = 3.0f;
}

void ABaseProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Log, TEXT("Onhit Test1"));
	// Only add impulse and destroy projectile if we hit a physics
	
	
	AEnemyBaseCharacter* Enemy = Cast<AEnemyBaseCharacter>(Hit.GetActor());
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetInstigator());

	FVector HitLocation = Hit.ImpactPoint;//맞은 지점 표시

	if (Enemy) {
		if (MonsterParticleSystem) {
			FVector SocketLocation = Hit.Location;
			FRotator SocketRotation = Hit.ImpactPoint.Rotation();
			FTransform SocketTransform = Hit.GetActor()->GetActorTransform();

			ParticleSystemComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MonsterParticleSystem, SocketLocation, SocketRotation);
			//ParticleSystemComp->SetWorldScale3D(SocketTransform.GetScale3D());
		}
	}
	else {
		if (ExtraParticleSystem) {
			FVector SocketLocation = Hit.Location;
			FRotator SocketRotation = Hit.ImpactPoint.Rotation();
			FTransform SocketTransform = Hit.GetActor()->GetActorTransform();

			ParticleSystemComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExtraParticleSystem, SocketLocation, SocketRotation);
			//ParticleSystemComp->SetWorldScale3D(SocketTransform.GetScale3D());
		}
		
	}



	// 0에서 1 사이의 랜덤한 값을 생성합니다.
	float RandomValue = FMath::FRand();
	
	float Damage;
	bool Oncritical;
	if (Enemy) {
		if (RandomValue < Player->GetCriticalChance()) { //크리티컬이 발생했다면
			Damage = Player->GetAttackDamage() * Player->GetCriticalDamage();
			Oncritical = true;
		}
		else {
			Damage = Player->GetAttackDamage();
			Oncritical = false;
		}
		Enemy->ApplyDamage(Damage, Oncritical, HitLocation, Player);
	}

	Destroy();
}

void ABaseProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}



