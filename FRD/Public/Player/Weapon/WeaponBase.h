// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/BaseProjectile.h"
#include "WeaponBase.generated.h"


class APlayerCharacter;


UCLASS()
class FRD_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
	

public:	
	// Sets default values for this actor's properties
	AWeaponBase();

	

	inline int GetAmmoCount() { return AmmoMaxCount; }
	void SetAmmoCount(int Ammo) { AmmoMaxCount = Ammo; }
	inline float GetReloadingDelayTime() { return ReloadingDelayTime; }

protected:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* SkeletalMeshComp;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Particles")
	class UParticleSystemComponent* ParticleSystemComp;

	UPROPERTY(EditAnywhere, Category = "Particles")
	class UParticleSystem* ParticleSystem;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ABaseProjectile> ProjectileClass;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* ReloadAnimation;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* FireSound;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* ReloadSound;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ReloadAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ChangeAutoAction;

	/** 탄약 최대 개수 */
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
	int AmmoMaxCount = 30;

	/** 현재 소지한 탄약의 개수*/
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
	int AmmoRemainCount;

	/** 재장전까지 걸리는 시간 */
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
	float ReloadingDelayTime = 1.f;

	/** 발사 간의 간격 */
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
	float FireInterval = 0.1f;


	// 카메라 컴포넌트
	class UCameraComponent* CameraComponent;


	// 반동 힘
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
	float PitchRecoil;

	// 반동 값을 적용할 때의 감쇠 정도
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
	float YawRecoil;

	// 총알이 발사될 때 호출되는 함수
	void ApplyRecoil(class ABasePlayerController* PController);

	bool isAuto = true;

	bool isReloading = false;

	UPROPERTY(EditAnywhere, Category = "Weapon Types", meta = (AllowPrivateAccess = "true")) //무기타입 0 = 근접 1 = 두손 총 2 = 한손총
	int WeaponType;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:	
	
	USkeletalMeshComponent* GetSkeletalMeshComp() {	return SkeletalMeshComp;}

	virtual void mapping(APlayerCharacter* Player);

	/** 발사를 시작하는 메서드 */
	virtual void StartFire(APlayerCharacter* Player);

	/** 발사를 멈추는 메서드*/
	virtual void StopFire(APlayerCharacter* Player);

	/** 재장전 메서드*/
	virtual void Reloading(APlayerCharacter* Player);

	virtual void EndReload(APlayerCharacter* Player);

	virtual void ChangeAuto();


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int GetWeaponType() { return WeaponType; }

	TSubclassOf<class ABaseProjectile> GetProjectile() {return ProjectileClass;	}

	void SetProjectile(TSubclassOf<class ABaseProjectile> Projectile);
	
};
