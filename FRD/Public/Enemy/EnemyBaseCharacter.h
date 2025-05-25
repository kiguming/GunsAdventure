
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy/MoneyActor.h"
#include "EnemyBaseCharacter.generated.h"



USTRUCT(BlueprintType)
struct FMonsterStats
{
	GENERATED_BODY()

	//최대 체력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player stat")
	float MaxHealth; 

	//현재 체력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player stat")
	float Health; 

	//몬스터 공격력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player stat")
	float AttackDamage; 

	//캐릭터 기본 이동 속도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player stat")
	float MonsterSpeed; 

	//캐릭터 방어력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player stat")
	float Def;

	//캐릭터 경험치
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player stat")
	float Exp; 

};

UCLASS()
class FRD_API AEnemyBaseCharacter : public ACharacter
{
	GENERATED_BODY()

	FTimerHandle TimerHandle_WidgetLifetimeExpired;

public:
	// Sets default values for this character's properties
	AEnemyBaseCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* ApplySound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* AttackAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* DeadAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	TSubclassOf<class ADamageActor> DamageActorClass;

	FTimerHandle RemoveTimeHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 구조체 변수
	UPROPERTY(EditAnywhere, Category = "Monster stat")
	FMonsterStats MonsterStats;
	
	int deading = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Exp")
	TSubclassOf<class AMoneyActor> Moneyclass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetHealth(float Health) {	MonsterStats.Health = Health;}
	void SetAttackDamage(float AttackDamage) { MonsterStats.AttackDamage = AttackDamage; }
	void SetMonsterSpeed(float MonsterSpeed) { MonsterStats.MonsterSpeed = MonsterSpeed; }
	void SetDef(float Def) {	MonsterStats.Def = Def;	}

	float GetHealth() { return MonsterStats.Health; }
	float GetAttackDamage() { return MonsterStats.AttackDamage; }
	float GetMonsterSpeed() { return MonsterStats.MonsterSpeed; }
	float GetDef() { return MonsterStats.Def; }

	void ApplyDamage(float Damage,bool Oncritical, FVector HitLocation, class APlayerCharacter* Player);

	void Ondead();

	UFUNCTION(BlueprintCallable)
	void Attack();
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** 무언가가 구체 컴포넌트를 나설 때 호출 */
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void Deleting();

	
};
