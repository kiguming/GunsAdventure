// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserArgument.generated.h"

/**
 * 
 */
UCLASS()
class FRD_API UUserArgument : public UUserWidget
{
	GENERATED_BODY()

	FTimerHandle TimerHandle;

	class ABasePlayerController* PController;

public:

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* EffectSound;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* Panel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UGridPanel* GridPanel1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UGridPanel* GridPanel2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UGridPanel* GridPanel3;


	UPROPERTY(BlueprintReadWrite)
	class UArgumentBaseWidget* Argument_Card1;

	UPROPERTY(BlueprintReadWrite)
	class UArgumentBaseWidget* Argument_Card2;

	UPROPERTY(BlueprintReadWrite)
	class UArgumentBaseWidget* Argument_Card3;

	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void showArgu();
};
