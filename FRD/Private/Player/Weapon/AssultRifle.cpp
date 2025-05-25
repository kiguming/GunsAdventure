// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Weapon/AssultRifle.h"
#include "Player/PlayerCharacter.h"
#include "Player/BasePlayerController.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Player/BaseProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

AAssultRifle::AAssultRifle()
{
	WeaponType = 1;
}

void AAssultRifle::BeginPlay()
{
	Super::BeginPlay();
}

void AAssultRifle::StartFire(APlayerCharacter* Player)
{

	Super::StartFire(Player);
	auto Character = Player;

	if (!isReloading) {//재장전 상태가 아닐때만 발사해라.
		if (!isAuto) {
			GoFire(Character);
		}
		else {
			if (Character) {
				GetWorldTimerManager().SetTimer(FireTimerHandle, [Character, this]() { GoFire(Character); }, FireInterval, true);
			}
		}
	}
	
	
	
	

	
}

void AAssultRifle::StopFire(APlayerCharacter* Player)
{
	Super::StopFire(Player);
	if (FireTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(FireTimerHandle);
	}
	
}

void AAssultRifle::Reloading(APlayerCharacter* Player)
{
	Super::Reloading(Player);
	
}

void AAssultRifle::EndReload(APlayerCharacter* Player)
{
	Super::EndReload(Player);

	
}

void AAssultRifle::GoFire(APlayerCharacter* Character)
{
	UE_LOG(LogTemp, Log, TEXT("GoFire Starting"));

	

	// 탄약이 남아있지 않거나 죽으면 발사를 중지합니다.
	if (AmmoRemainCount <= 0 || Character->GetOndead())
	{
		StopFire(Character);
		return;
	}

	if (Character)
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
		AController* Controller = Character->GetController();
		if (!Controller)
		{
			UE_LOG(LogTemp, Warning, TEXT("Controller not found."));
			return;
		}

		// 플레이어 컨트롤러로 캐스트합니다.
		ABasePlayerController* PlayerController = Cast<ABasePlayerController>(Controller);
		if (!PlayerController || !PlayerController->PlayerCameraManager)
		{
			UE_LOG(LogTemp, Warning, TEXT("PlayerController or PlayerCameraManager not found."));
			return;
		}

		// 카메라의 회전을 가져옵니다.
		const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();

		
		

		const FVector SpawnLocation = Character->GetFPPMuzzle()->GetComponentLocation();

		

		if (SpawnLocation == FVector::ZeroVector)
		{
			UE_LOG(LogTemp, Warning, TEXT("Muzzle Socket not found."));
			return;
		}

		

		// 발사체를 스폰합니다.
		AmmoRemainCount--;
		ApplyRecoil(PlayerController);
		PlayerController->GetInstance()->UpdateAmmoCount(AmmoRemainCount, AmmoMaxCount);
		
		if (ParticleSystem) {
			FVector SocketLocation = SkeletalMeshComp->GetSocketLocation("Muzzle");
			FRotator SocketRotation = SkeletalMeshComp->GetSocketRotation("Muzzle");
			FTransform SocketTransform = SkeletalMeshComp->GetSocketTransform("Muzzle");
			ParticleSystemComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, SocketLocation, SocketRotation);
			ParticleSystemComp->SetWorldScale3D(SocketTransform.GetScale3D());
		}

		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.Instigator = Character;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		World->SpawnActor<ABaseProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		
		// 발사 소리를 재생합니다.
		if (FireSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
		}

		// 발사 애니메이션을 재생합니다.
		if (FireAnimation)
		{
			Character->PlayFireAnimation(FireAnimation);
		}
	}

	
}


void AAssultRifle::ChangeAuto()
{
	if (isAuto) {
		isAuto = false;
	}
	else {
		isAuto = true;
	}
}
