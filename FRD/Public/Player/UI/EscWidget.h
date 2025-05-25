// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EscWidget.generated.h"

/**
 * 
 */
UCLASS()
class FRD_API UEscWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	class UBaseSaveGame* LoadGameInstance;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnchangeScreen();

	UFUNCTION()
	void OnClickEsc();

	UFUNCTION()
	void OnClickReturn();

	UFUNCTION()
	void ChangeSound(float Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UComboBoxString* ResolutionComboBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCheckBox* FullScreenCheck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ScreenOkButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* EscButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ReturnButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class USlider* Slider_sound;

};
