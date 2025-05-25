// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Animation/PlayerAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Player/PlayerCharacter.h"



void UPlayerAnimInstance::UpdateProperties()
{
	if (!PlayerPawn)
		PlayerPawn = TryGetPawnOwner();

	if (PlayerPawn)
	{
		// 공중에 있는지
		BIsInAir = PlayerPawn->GetMovementComponent()->IsFalling();

		// Z축이 필요없기 때문에 Z는 0.f로 처리해서 속력를 구한다
		FVector velocity = PlayerPawn->GetVelocity();
		velocity = FVector(velocity.X, velocity.Y, 0.f);
		MovementSpeed = FVector(velocity.X, velocity.Y, 0.f).Size();

		// 속도 벡터를 정규화하여 이동 방향을 얻음
		FVector VelocityDirection = velocity.GetSafeNormal();

		// 속도 벡터가 0이 아닌 경우에만 방향을 계산
		if (!VelocityDirection.IsNearlyZero())
		{
			// 이동 방향을 바탕으로 플레이어 캐릭터의 회전 값을 계산
			FRotator Rotation = VelocityDirection.Rotation();

			// 플레이어 캐릭터의 회전 값을 방향으로 사용
			Direction = Rotation.Yaw;
		}
		else
		{
			// 속도가 0이면 방향을 0으로 설정하거나 이전 방향 값을 유지할 수 있음
			Direction = 0.0f;
		}
		
		//Aim_Yaw = PlayerPawn->GetBaseAimRotation().Yaw;
		//Aim_Pitch = PlayerPawn->GetBaseAimRotation().Pitch;
		

		Aim_Yaw = FMath::Clamp(PlayerPawn->GetBaseAimRotation().Yaw, -90, 90);
		Aim_Pitch = FMath::Clamp(PlayerPawn->GetBaseAimRotation().Pitch, -55, 55);
		APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());
		if (Player) {
			BIsCrouch = Player->Biscrouch;
			if (Player->GetWeapon()) {
				WeaponType = Player->GetWeaponType();
			}
			else {
				WeaponType = 0;
			}
			
		}
	}


}


void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	UpdateProperties();
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (!PlayerPawn)
	{
		PlayerPawn = TryGetPawnOwner();	// 소유자의 Pawn를 가져온다.
	}
}
