// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Setting_Ui.generated.h"

/**
 * 
 */
UCLASS()
class FRD_API USetting_Ui : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	class UBaseSaveGame* LoadGameInstance;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnchangeScreen();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UComboBoxString* ResolutionComboBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCheckBox* FullScreenCheck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ScreenOkButton;


};
