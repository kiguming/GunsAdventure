// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Weapon/ARReloadNotifyState.h"
#include "Player/Weapon/AssultRifle.h"
#include "Player/PlayerCharacter.h"

void UARReloadNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    APlayerCharacter* Player = Cast<APlayerCharacter>(MeshComp->GetOwner());
    if (Player)
    {
        AWeaponBase* Weapon = Cast<AWeaponBase>(Player->GetWeapon());
        if (Weapon) {
            UE_LOG(LogTemp, Log, TEXT("AR Change OKay. %s"));
            Weapon->EndReload(Player);
        }
    }
    UE_LOG(LogTemp, Log, TEXT("Reload end?"));

}
