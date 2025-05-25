// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArguActor.generated.h"

class APlayerCharacter;

USTRUCT(BlueprintType)
struct FAddStatus
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arguments stat")
	float Health = 100.0f; //최대 체력 증가

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arguments stat")
	float AttackDamage = 0.0f; //데미지 증가

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arguments stat")
	float PlayerSpeed = 0.0f; //캐릭터 추가 이동 속도

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arguments stat")
	float Def = 0.0f; //캐릭터 방어력

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arguments stat")
	float ReloadingSpeed = 0.0f; //공격 속도

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arguments stat")
	float CriticalChance = 0.0f; //치명 확률

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arguments stat")
	float CriticalDamage = 0.0f; //치명 추가데미지

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arguments stat")
	float addDamage = 0.0f; //조건부 추가 데미지

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arguments stat")
	float addSpeed = 0.0f; //조건부 추가 스피드

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arguments stat")
	int addOn = 0; //에드온 갯수

};

UCLASS(Blueprintable)
class FRD_API AArguActor : public AActor
{
	GENERATED_BODY()
	
	// 구조체 변수
	UPROPERTY(EditAnywhere, Category = "Arguments stat")
	FAddStatus Adder;

public:	
	// Sets default values for this actor's properties
	AArguActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetStat(APlayerCharacter* Player);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTexture2D* Texture;

	FAddStatus GetAdder() const { return Adder; }
	UTexture2D* GetTexture() { return Texture; }

	void SetAdder(FAddStatus Add) { Adder = Add; }
	void SetImg(UTexture2D* Img) { Texture = Img;	UE_LOG(LogTemp, Log, TEXT("이미지 변경")); }

};
