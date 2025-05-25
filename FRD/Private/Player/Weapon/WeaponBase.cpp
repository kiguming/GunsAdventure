// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Weapon/WeaponBase.h"
#include "Player/PlayerCharacter.h"
#include "Player/BaseProjectile.h"
#include "Enemy/EnemybaseCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/SkeletalMeshComponent.h"
#include "Player/BasePlayerController.h"
#include "Camera/CameraComponent.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// RootComponent를 설정합니다.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// SkeletalMeshComp를 생성하고 RootComponent에 부착합니다.
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	SkeletalMeshComp->SetCastShadow(false);
	SkeletalMeshComp->SetupAttachment(RootComponent);
	WeaponType = 0;
	PitchRecoil = 0.1;
	YawRecoil = 0.1;
}

void AWeaponBase::ApplyRecoil(class ABasePlayerController* PController)
{
	

	// 랜덤한 반동 값을 생성 (예시로 -10부터 10까지의 랜덤한 값 생성)
	float RandomPitch = FMath::FRandRange(-PitchRecoil, 0);
	float RandomYaw = FMath::FRandRange(-YawRecoil, YawRecoil);

	PController->AddPitchInput(RandomPitch);
	PController->AddYawInput(RandomYaw);
	
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaponBase::mapping(APlayerCharacter* Player)
{
	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Player->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AWeaponBase::StartFire, Player);
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &AWeaponBase::StopFire, Player);
			EnhancedInputComponent->BindAction(ChangeAutoAction, ETriggerEvent::Triggered, this, &AWeaponBase::ChangeAuto);
			EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &AWeaponBase::Reloading, Player);
		}
	}

}

void AWeaponBase::StartFire(APlayerCharacter* Player)
{
	
	//상속받은 곳에서 만듬
	if (ABasePlayerController* PlayerController = Cast<ABasePlayerController>(Player->GetController())) {
		
		PlayerController->GetInstance()->UpdateAmmoCount(AmmoRemainCount, AmmoMaxCount);
	}
}

void AWeaponBase::StopFire(APlayerCharacter* Player)
{
	isReloading = false;
}

void AWeaponBase::Reloading(APlayerCharacter* Player)
{


	if (!isReloading) {//재장전 상태가 아닐때만 실행
		isReloading = true; // 재장전 상태로 바꿈.
		AmmoRemainCount = 0; //재장전 할때 총알 0발로 바꿈
		if (ReloadAnimation)
		{
		float ReloadSpeed = FMath::Min(5.0f, ReloadingDelayTime + Player->GetReloadingSpeed());//재장전 속도를 최대 재생 속도를 5.0f가 되게끔 설정.
		Player->PlayMontage(ReloadAnimation, ReloadSpeed);
		if (!ReloadSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, Player->GetActorLocation());
		}
		}
	}
	
	
}

void AWeaponBase::EndReload(APlayerCharacter* Player)
{
	AmmoRemainCount = AmmoMaxCount; // 총알을 재장전하고
	if (ABasePlayerController* PlayerController = Cast<ABasePlayerController>(Player->GetController())) {
		PlayerController->GetInstance()->UpdateAmmoCount(AmmoRemainCount, AmmoMaxCount);
	}
	isReloading = false; //리로딩 상태를 해제합니다.
}

void AWeaponBase::ChangeAuto()
{
	//상속받은 곳에서 만듬.
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::SetProjectile(TSubclassOf<ABaseProjectile> Projectile)
{
	ProjectileClass = Projectile;
}

