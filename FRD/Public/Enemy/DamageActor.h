// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageActor.generated.h"

UCLASS()
class FRD_API ADamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageActor();

	void Initialize(float Damage, bool IsCritical);



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    // Function to handle the lifetime of the actor
    void DestroyText();

    // Text component to display damage
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DamageText")
    class UTextRenderComponent* DamageTextComponent;

    // Lifetime of the actor (in seconds)
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DamageText")
    float Lifetime;

    // Movement speed of the actor
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DamageText")
    float MovementSpeed;

   

    FTimerHandle TimerHandle_Destroy;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
