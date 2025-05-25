// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Player/UI/MainWidget.h"
#include "Player/UI/UserArgument.h"
#include "Player/UI/ArguActor.h"
#include "Player/UI/GameEndWidget.h"
#include "BasePlayerController.generated.h"


/**
 * 
 */
UCLASS()
class FRD_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
	ABasePlayerController();

	int PlayerLevel;

	FTimerHandle DeadTimerHandler;

	

	

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* DeathSound;

	void ArgumentStart();

	void ArgumentStop();
	
	void UpdateLevel();

	int GetLevel() const { return PlayerLevel; }

	void changeHp(float percent);

	void Ondead();

	void OndeadAfter();

	UMainWidget* GetInstance() {return MainWidgetInstance;	}

	TSubclassOf<class UArgumentBaseWidget> GetArgu(int numbers) {	return Argument_Lists[numbers];	}

protected:
	virtual void BeginPlay() override;

	// 사용자 인터페이스에 대한 포인터 선언
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UMainWidget> MainWidgetClass;

	// 실제 사용자 인터페이스 객체
	UMainWidget* MainWidgetInstance;

	// 사용자 인터페이스에 대한 포인터 선언
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UGameEndWidget> GameEndWidgetClass;

	// 실제 사용자 인터페이스 객체
	UGameEndWidget* GameEndWidgetInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UArguShopWidget> Argushop;


	// 클래스 멤버 변수로 유저 인터페이스 객체를 추가합니다.
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> LevelUpWidgetClass;

	UUserArgument* LevelUpWidgetInstance;
	
	void ShuffleArray(TArray<TSubclassOf<UArgumentBaseWidget>>& Array);//랜덤으로 배열섞기

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TArray<TSubclassOf<class UArgumentBaseWidget>> Argument_Lists;

};
