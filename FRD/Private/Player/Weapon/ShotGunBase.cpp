// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Weapon/ShotGunBase.h"
#include "Player/BasePlayerController.h"
#include "Player/PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

AShotGunBase::AShotGunBase()
{
	WeaponType = 1;//시작은 양손 입니다. 변경가능합니다.
}

void AShotGunBase::StartFire(APlayerCharacter* Player)
{
	Super::StartFire(Player);
	// 탄약이 남아있지 않으면 발사를 중지합니다.
	if (AmmoRemainCount <= 0)
	{
		StopFire(Player);
		return;
	}

	if (Player)
	{
		UE_LOG(LogTemp, Log, TEXT("GoFire Cast"));

		// 월드를 가져옵니다.
		UWorld* const World = GetWorld();
		if (!World)
		{
			UE_LOG(LogTemp, Warning, TEXT("World not found."));
			return;
		}

		// 캐릭터의 컨트롤러를 가져옵니다.
		AController* Controller = Player->GetController();
		if (!Controller)
		{
			UE_LOG(LogTemp, Warning, TEXT("Controller not found."));
			return;
		}

		// 플레이어 컨트롤러로 캐스트합니다.
		ABasePlayerController* PController = Cast<ABasePlayerController>(Controller);
		if (!PController || !PController->PlayerCameraManager)
		{
			UE_LOG(LogTemp, Warning, TEXT("PlayerController or PlayerCameraManager not found."));
			return;
		}

		// 카메라의 회전을 가져옵니다.
		const FRotator SpawnRotation = PController->PlayerCameraManager->GetCameraRotation();

		const FVector SpawnLocation = Player->GetFPPMuzzle()->GetComponentLocation();



		if (SpawnLocation == FVector::ZeroVector)
		{
			UE_LOG(LogTemp, Warning, TEXT("Muzzle Socket not found."));
			return;
		}
		
		AmmoRemainCount--;
		ApplyRecoil(PController);
		// 발사체 스폰
		if (ParticleSystem) {
			FVector SocketLocation = SkeletalMeshComp->GetSocketLocation("Muzzle");
			FRotator SocketRotation = SkeletalMeshComp->GetSocketRotation("Muzzle");
			FTransform SocketTransform = SkeletalMeshComp->GetSocketTransform("Muzzle");
			ParticleSystemComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, SocketLocation, SocketRotation);
			ParticleSystemComp->SetWorldScale3D(SocketTransform.GetScale3D());
		}

		const int32 NumProjectilesToSpawn = ShotgunGage; // 숫자 조절해서 발사체 수 조정
		const float SpreadAngle = 7.0f; // 발사체 퍼짐 각도
		for (int32 i = 0; i < NumProjectilesToSpawn; ++i)
		{
			const FRotator RandomSpreadRotation = FRotator(FMath::RandRange(-SpreadAngle, SpreadAngle),
				FMath::RandRange(-SpreadAngle, SpreadAngle),
				FMath::RandRange(-SpreadAngle, SpreadAngle));
			const FRotator FinalSpawnRotation = SpawnRotation + RandomSpreadRotation;

			
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.Instigator = Player;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			World->SpawnActor<ABaseProjectile>(ProjectileClass, SpawnLocation, FinalSpawnRotation, ActorSpawnParams);
		}


		PController->GetInstance()->UpdateAmmoCount(AmmoRemainCount, AmmoMaxCount);


		// 발사 소리를 재생합니다.
		if (FireSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, Player->GetActorLocation());
		}

		// 발사 애니메이션을 재생합니다.
		if (FireAnimation)
		{
			Player->PlayFireAnimation(FireAnimation);
		}
	}
}

int AShotGunBase::GetShotgunGage()
{
	return ShotgunGage;
}
