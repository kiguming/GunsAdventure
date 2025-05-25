// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UI/UserArgument.h"
#include "Components/Button.h"
#include "Player/UI/ArgumentBaseWidget.h"
#include "Player/PlayerCharacter.h"
#include "Player/UI/ArguActor.h"
#include "Player/BasePlayerController.h"
#include "Components/CanvasPanel.h"
#include "Components/GridPanel.h"
#include "Kismet/GameplayStatics.h"

void UUserArgument::NativeConstruct()
{
	
	PController = Cast<ABasePlayerController>(GetOwningPlayer());

	UE_LOG(LogTemp, Log, TEXT("플레이어 컨트롤러 처리1"));
	if (PController) {
		
		

		Argument_Card1 = CreateWidget<UArgumentBaseWidget>(GetWorld(), PController->GetArgu(0));
		Argument_Card2 = CreateWidget<UArgumentBaseWidget>(GetWorld(), PController->GetArgu(1));
		Argument_Card3 = CreateWidget<UArgumentBaseWidget>(GetWorld(), PController->GetArgu(2));
		
	

		GridPanel1->AddChildToGrid(Argument_Card1);
		GridPanel2->AddChildToGrid(Argument_Card2);
		GridPanel3->AddChildToGrid(Argument_Card3);
		if (EffectSound) {
			UGameplayStatics::PlaySoundAtLocation(this, EffectSound, PController->GetSpawnLocation());
		}
		
	}
}

void UUserArgument::showArgu()
{
	
}



