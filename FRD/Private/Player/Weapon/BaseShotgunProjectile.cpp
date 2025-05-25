// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Weapon/BaseShotgunProjectile.h"
#include "Player/BaseProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Enemy/EnemyBaseCharacter.h"
#include "Player/PlayerCharacter.h"
#include "Math/UnrealMathUtility.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Weapon/ShotGunBase.h"

void ABaseShotgunProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Log, TEXT("Onhit Test1"));
	// Only add impulse and destroy projectile if we hit a physics


	AEnemyBaseCharacter* Enemy = Cast<AEnemyBaseCharacter>(Hit.GetActor());
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetInstigator());

	AShotGunBase* Weapon = Cast<AShotGunBase>(Player->GetWeapon());

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
	if (Weapon) {
		if (Enemy) {
			if (RandomValue < Player->GetCriticalChance()) { //크리티컬이 발생했다면
				Damage = Player->GetAttackDamage() * Player->GetCriticalDamage();
				Damage /= Weapon->GetShotgunGage();
				Oncritical = true;
			}
			else {
				Damage = Player->GetAttackDamage();
				Damage /= Weapon->GetShotgunGage();
				Oncritical = false;
			}
			Enemy->ApplyDamage(Damage, Oncritical, HitLocation, Player);
		}
	}
	else {
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
	}
	

	Destroy();
}
