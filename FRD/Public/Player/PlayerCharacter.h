// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class BasePlayerController;
struct FInputActionValue;
class USpringArmComponent;
class USphereComponent;
class AWeaponBase;

USTRUCT(BlueprintType)
struct FPlayerStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player stat")
	float MaxHealth; //최대 체력

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player stat")
	float Health; //현재 체력

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player stat")
	float AttackDamage; //데미지

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player stat")
	float PlayerSpeed; //캐릭터 추가 이동 속도
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player stat")
	float Def; //캐릭터 방어력

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player stat")
	float ReloadingSpeed; //장전 속도

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player stat")
	float CriticalChance; //치명 확률

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player stat")
	float CriticalDamage; //치명 추가데미지

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop Player stat")//상점 구매당 추가 치확
	float AddCriChance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop Player stat")//상점 구매당 추가 치뎀
	float AddCriDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop Player stat")//상점 구매당 추가 방어력
	float AddDef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop Player stat")//상점 구매당 추가 데미지
	float AddDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop Player stat")//상점 구매당 추가 스피드
	float AddSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop Player stat")//상점 구매당 추가 체력
	float AddHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop Player stat")//상점 구매당 추가 탄약
	int AddAmmo;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop Player stat")//상점 구매당 추가 재장전속도
	float AddReload;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player stat")
	int addOn; //에드온 갯수

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player stat")
	float Exp; //경험치

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player stat")
	float MaxExp; //최대경험치

	int Money;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player stat")//0번기본총 1번 라이플 2번 샷건 4번...
	int WeaponNumber;

};

UCLASS()
class FRD_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()
	
	// 구조체 변수
	UPROPERTY(EditAnywhere, Category = "Player stat")
	FPlayerStats PlayerStats;


	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* ThirdPersonCameraComponent;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* DeadCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USphereComponent* FPPMuzzle;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ChangeSight;
	
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DebugKey;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RunAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShowStatAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* EscAction;

	UPROPERTY(EditAnyWhere, Category = "Weapon", meta = (AllowPrivateAccess = "true"))//기본 총 권총
	TSubclassOf<AWeaponBase> Weapon;

	UPROPERTY(EditAnyWhere, Category = "Weapon", meta = (AllowPrivateAccess = "true"))//상점 2번째 구매 총 라이플
	TSubclassOf<AWeaponBase> SecondWeapon; 

	UPROPERTY(EditAnyWhere, Category = "Weapon", meta = (AllowPrivateAccess = "true"))//상점 3번째 구매총 샷건
	TSubclassOf<AWeaponBase> ThirdWeapon; 

	UPROPERTY(EditAnywhere, Category = Gameplay)
	USoundBase* ApplySound;

	AWeaponBase* EquipWeapon;//1인칭 캐릭터가 장착한 무기

	AWeaponBase* ThirdEquippWeapon;//3인칭 캐릭터가 장착한 무기

	class UAnimInstance* AnimInstance;

	

	bool Ondead = false;
public:
	// Sets default values for this character's properties
	APlayerCharacter();

	USphereComponent* GetFPPMuzzle() {	return FPPMuzzle;}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* DeadAnimation;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	bool GetOndead() {return Ondead;}

public:
	void AttachWeapon(TSubclassOf<class AWeaponBase> weapon);
	void AttachWeapon3DMesh(TSubclassOf<class AWeaponBase> weapon);

	void WeaponUpgrade();
	void Debuging();
	bool Biscrouch;	
	bool bIsFirstPerson;

	class AWeaponBase* GetWeapon() {return EquipWeapon;	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	
	void StartRun();

	void StopRun();

	void ShowStat();

	void ShowEsc();

	

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FPlayerStats GetPlayerStats() {	return PlayerStats;	}

	void ApplyDamage(float Damage);

	void UpdateExp(float plusExp);

	void ChangeView();

	int GetMoney();

	void DeathEvent();

	void UpdateMoney(float Mount);

	void SetMaxHealth(float NewMaxHealth) { PlayerStats.MaxHealth = NewMaxHealth; }
	float GetMaxHealth() const { return PlayerStats.MaxHealth; }

	void SetHealth(float NewHealth) { PlayerStats.Health = NewHealth; }
	float GetHealth() const { return PlayerStats.Health; }

	void SetAttackDamage(float NewAttackDamage) { PlayerStats.AttackDamage = NewAttackDamage; }
	float GetAttackDamage() const { return PlayerStats.AttackDamage; }

	void SetPlayerSpeed(float NewPlayerSpeed) { PlayerStats.PlayerSpeed = NewPlayerSpeed; }
	float GetPlayerSpeed() const { return PlayerStats.PlayerSpeed; }

	void SetDef(float NewDef) { PlayerStats.Def = NewDef; }
	float GetDef() const { return PlayerStats.Def; }

	void SetReloadingSpeed(float NewReloadingSpeed) { PlayerStats.ReloadingSpeed = NewReloadingSpeed; }
	float GetReloadingSpeed() const { return PlayerStats.ReloadingSpeed; }

	void SetCriticalChance(float NewCriticalChance) { PlayerStats.CriticalChance = NewCriticalChance; }
	float GetCriticalChance() const { return PlayerStats.CriticalChance; }

	void SetCriticalDamage(float NewCriticalDamage) { PlayerStats.CriticalDamage = NewCriticalDamage; }
	float GetCriticalDamage() const { return PlayerStats.CriticalDamage; }

	void SetAddDamage(float NewAddDamage) { PlayerStats.AddDamage = NewAddDamage; }
	float GetAddDamage() const { return PlayerStats.AddDamage; }

	void SetAddSpeed(float NewAddSpeed) { PlayerStats.AddSpeed = NewAddSpeed; }
	float GetAddSpeed() const { return PlayerStats.AddSpeed; }

	void SetAddOn(int NewAddOn) { PlayerStats.addOn = NewAddOn; }
	int GetAddOn() const { return PlayerStats.addOn; }

	void SetExp(float NewExp) { PlayerStats.Exp = NewExp; }
	float GetExp() const { return PlayerStats.Exp; }

	void SetMaxExp(float NewMaxExp) { PlayerStats.MaxExp = NewMaxExp; }
	float GetMaxExp() const { return PlayerStats.MaxExp; }

	int GetWeaponType();

	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	void PlayFireAnimation(UAnimMontage* FireAnimation);

	void PlayMontage(UAnimMontage* PlayAnimation, float Speed);
};
