// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/DamageActor.h"
#include "Components/TextRenderComponent.h"
#include "TimerManager.h"
#include "Player/BasePlayerController.h"

// Sets default values
ADamageActor::ADamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create and initialize the text component
    DamageTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("DamageTextComponent"));
    DamageTextComponent -> SetupAttachment(RootComponent);
    RootComponent = DamageTextComponent;

    // Set default properties
    Lifetime = 2.0f;
    MovementSpeed = 50.0f;

    DamageTextComponent->bCastDynamicShadow = false;

    
}

void ADamageActor::Initialize(float Damage, bool IsCritical)
{
   
    FString DamageText = FString::Printf(TEXT("%.0f"), Damage);
    DamageTextComponent->SetText(FText::FromString(DamageText));
    DamageTextComponent->SetTextRenderColor(IsCritical ? FColor::Magenta : FColor::Blue);
}

// Called when the game starts or when spawned
void ADamageActor::BeginPlay()
{
	Super::BeginPlay();

    GetWorldTimerManager().SetTimer(TimerHandle_Destroy, this, &ADamageActor::DestroyText, Lifetime, false);
}

void ADamageActor::DestroyText()
{
    Destroy();
}

// Called every frame
void ADamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

