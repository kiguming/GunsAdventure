// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/GoblinbossCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


void AGoblinbossCharacter::Bossattack()
{
	if (GetHealth() >= 400) {
		if (AttackAnimation != nullptr)
		{

			if ((rand() % 2) == 1) {
				PlayAnimMontage(AttackAnimation1);				
			}
			else {
				PlayAnimMontage(AttackAnimation2);
			}
			

		}
	}
	else {
		PlayAnimMontage(AnotherAnimation);

	}
}
