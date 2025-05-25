// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "COmponents/Image.h"
#include "ArgumentBaseWidget.generated.h"

class APlayerCharacter;

USTRUCT(BlueprintType)
struct FAdder
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arguments stat")//최대 체력 증가
	float Health = 0.0f; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arguments stat")//데미지 증가
	float AttackDamage = 0.0f; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arguments stat")//캐릭터 추가 이동 속도
	float PlayerSpeed = 0.0f; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arguments stat")//캐릭터 방어력
	float Def = 0.0f; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arguments stat")//재장전 속도
	float ReloadingSpeed = 0.0f; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arguments stat")//치명 확률
	float CriticalChance = 0.0f; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arguments stat")//치명 추가데미지
	float CriticalDamage = 0.0f; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arguments stat") //총알갯수 추가
	int addAmmo = 0.0f; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arguments stat")//증강을 구매했는지 체크
	bool bIsbuy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arguments stat")//에드온 갯수
	int addOn = 0; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arguments stat")//증강 가격
	int Price = 0; 



};

/**
 * 
 */
UCLASS()
class FRD_API UArgumentBaseWidget : public UUserWidget
{
	GENERATED_BODY()

	// 구조체 변수
	UPROPERTY(EditAnywhere, Category = "Arguments stat")
	FAdder Adder;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* MyButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image;

	
public:

	UButton* GetButton() const { return MyButton; }
	FAdder GetAdder() const {return Adder;}
	UTexture2D* GetImg();

	void SetButton(UButton* Button) {	MyButton = Button;	}
	void SetAdder(FAdder Add) {Adder = Add;	}
	void SetImg(UTexture2D* Texture);
	UFUNCTION()
	virtual void ClickedButton();

	virtual void NativeConstruct() override;

	bool IsBuying() {return Adder.bIsbuy;	}

	void SetBuy(bool tof) { Adder.bIsbuy = tof; }

	int GetPrice() { return Adder.Price; }
};
