// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class FRD_API ABaseProjectile : public AActor
{
	GENERATED_BODY()

protected:
	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Particles")
	class UParticleSystemComponent* ParticleSystemComp;

	UPROPERTY(EditAnywhere, Category = "Particles")
	class UParticleSystem* MonsterParticleSystem;

	UPROPERTY(EditAnywhere, Category = "Particles")
	class UParticleSystem* ExtraParticleSystem;

public:	
	// Sets default values for this actor's properties
	ABaseProjectile();



	/** called when projectile hits something */
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComponent; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovementComponent; }

	// 발사 방향으로의 발사체 속도를 초기화하는 함수입니다.
	void FireInDirection(const FVector& ShootDirection);

	// 발사체 메시
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	UStaticMeshComponent* ProjectileMeshComponent;


};
