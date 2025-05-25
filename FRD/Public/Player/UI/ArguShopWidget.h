// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArguShopWidget.generated.h"

/**
 * 
 */
UCLASS()
class FRD_API UArguShopWidget : public UUserWidget
{
	GENERATED_BODY()
	
	class UBaseSaveGame* LoadInstance;

	int ArguCounter;
	
protected:

	UPROPERTY(meta = (BindWidget)) // 증강1번 가격
	class UTextBlock* ArgumentPrice1;

	UPROPERTY(meta = (BindWidget)) // 증강2번 가격
	class UTextBlock* ArgumentPrice2;

	UPROPERTY(meta = (BindWidget)) // 증강3번 가격
	class UTextBlock* ArgumentPrice3;

	UPROPERTY(meta = (BindWidget)) // 증강4번 가격
	class UTextBlock* ArgumentPrice4;
	
	UPROPERTY(meta = (BindWidget)) // 증강4번 가격
	class UTextBlock* isBuy1;

	UPROPERTY(meta = (BindWidget)) // 증강4번 가격
	class UTextBlock* isBuy2;

	UPROPERTY(meta = (BindWidget)) // 증강4번 가격
	class UTextBlock* isBuy3;

	UPROPERTY(meta = (BindWidget)) // 증강4번 가격
	class UTextBlock* isBuy4;

	UPROPERTY(meta = (BindWidget)) // 증강1번 구매버튼
	class UButton* ArgumentButton1;

	UPROPERTY(meta = (BindWidget)) // 증강2번 구매벝튼
	class UButton* ArgumentButton2;

	UPROPERTY(meta = (BindWidget)) // 증강3번 구매버튼
	class UButton* ArgumentButton3;

	UPROPERTY(meta = (BindWidget)) // 증강4번 구매버튼
	class UButton* ArgumentButton4;

	UPROPERTY(meta = (BindWidget)) // 이전 버튼
	class UButton* PrevButton;

	UPROPERTY(meta = (BindWidget)) // 이후 버튼
	class UButton* NextButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UVerticalBox* VerticalBox1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UVerticalBox* VerticalBox2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UVerticalBox* VerticalBox3;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UVerticalBox* VerticalBox4;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MoneysText;

	class UArgumentBaseWidget* BuyCard1;

	class UArgumentBaseWidget* BuyCard2;

	class UArgumentBaseWidget* BuyCard3;

	class UArgumentBaseWidget* BuyCard4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TArray<TSubclassOf<class UArgumentBaseWidget>> ShopArgument_Lists;

	UPROPERTY(meta = (BindWidget)) // 판매 적용 버튼
		class UCanvasPanel* YesNoBox;

	UPROPERTY(meta = (BindWidget)) // 판매 적용 버튼
		class UButton* YesButton;

	UPROPERTY(meta = (BindWidget)) // 판매 적용 버튼
		class UButton* NoButton;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void ClickNext();

	UFUNCTION()
	void ClickPrev();
	
	UFUNCTION()
	void ClickedArgu1();

	UFUNCTION()
	void ClickedArgu2();

	UFUNCTION()
	void ClickedArgu3();

	UFUNCTION()
	void ClickedArgu4();

	UFUNCTION()
	void ClickedBuyArgu1();

	UFUNCTION()
	void ClickedBuyArgu2();

	UFUNCTION()
	void ClickedBuyArgu3();

	UFUNCTION()
	void ClickedBuyArgu4();

	UFUNCTION()
	void ShowArgument();

	UFUNCTION()
	void ClearArgument();

	UFUNCTION()
	void CancleClicked();

public:
	TArray<TSubclassOf<class UArgumentBaseWidget>> GetShopArgu() { return ShopArgument_Lists; }

};
