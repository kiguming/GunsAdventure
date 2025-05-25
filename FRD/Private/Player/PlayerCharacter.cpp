// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Player/WeaponBaseComponent.h"
#include "Player/BasePlayerController.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Player/Weapon/WeaponBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/Save/BaseSaveGame.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(GetCapsuleComponent());
	CameraSpringArm->bUsePawnControlRotation = true; // 카메라가 플레이어 캐릭터의 회전을 따라갈 수 있도록 설정합니다.

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a third person camera component
	ThirdPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	ThirdPersonCameraComponent->SetRelativeLocation(FVector(-200.f, 0.f, 64.f)); // Position the camera
	ThirdPersonCameraComponent->bUsePawnControlRotation = true;

	//죽을때 처리하는 카메라
	DeadCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("DeadCamera"));
	DeadCameraComponent->SetupAttachment(GetCapsuleComponent());
	//DeadCameraComponent->SetRelativeLocation(FVector(470.0f, 0.f, 160.f));
	//DeadCameraComponent->SetRelativeRotation(FRotator(0.f,-45.f,-180.f));
	DeadCameraComponent->bUsePawnControlRotation = true;

	FirstPersonCameraComponent->SetupAttachment(CameraSpringArm);
	ThirdPersonCameraComponent->SetupAttachment(CameraSpringArm);
	DeadCameraComponent->SetupAttachment(CameraSpringArm);


	// 스프링 암의 길이와 각도 설정
	CameraSpringArm->TargetArmLength = 300.0f; // 스프링 암의 길이
	CameraSpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f)); // 스프링 암의 각도 설정

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	//Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	ThirdPersonCameraComponent->Deactivate();
	DeadCameraComponent->Deactivate();
	FirstPersonCameraComponent->Activate();
	Mesh1P->SetVisibility(true);
	GetMesh()->SetVisibility(false);
	
	FPPMuzzle = CreateDefaultSubobject<USphereComponent>(TEXT("FPPMuzzle"));
	FPPMuzzle->SetupAttachment(FirstPersonCameraComponent);
	FPPMuzzle->BodyInstance.SetCollisionProfileName("NoCollision");
	FPPMuzzle->InitSphereRadius(15.0f);
	FPPMuzzle->SetRelativeLocation(FVector(50.0f, 0.0f, 0.0f));
	


	bIsFirstPerson = true;
	


	PlayerStats.MaxHealth = 1000.0f;

	PlayerStats.Health = 1000.0f;

	PlayerStats.AttackDamage = 10.0f;

	PlayerStats.PlayerSpeed = 600.0;

	PlayerStats.Def = 1.0f;

	PlayerStats.ReloadingSpeed = 0.0f;

	PlayerStats.CriticalChance = 0.1f;

	PlayerStats.CriticalDamage = 1.5f;

	
	PlayerStats.AddCriChance = 0.1f;

	PlayerStats.AddCriDamage = 0.1f;

	PlayerStats.AddDef = 3.0f;

	PlayerStats.AddDamage = 5.0f;

	PlayerStats.AddSpeed = 50.0f;

	PlayerStats.AddHealth = 50.0f;

	PlayerStats.AddAmmo = 5;

	PlayerStats.AddReload = 0.1;

	PlayerStats.addOn = 1;
	
	PlayerStats.Exp = 0.f;
	
	PlayerStats.MaxExp = 2.f;

	

}



// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	UBaseSaveGame* LoadGameInstance = Cast<UBaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UBaseSaveGame::StaticClass()));
	if (LoadGameInstance) {
		LoadGameInstance->SaveSlotName = "MyGames";
		LoadGameInstance->UserIndex = 0;
		LoadGameInstance = Cast<UBaseSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
		UE_LOG(LogTemp, Log, TEXT("게임을 불러옴"));
		if (!LoadGameInstance) {
			LoadGameInstance = NewObject<UBaseSaveGame>();
			UE_LOG(LogTemp, Log, TEXT("불러올게 없다면 새로 만듬"));
			LoadGameInstance->SaveSlotName = "MyGames";
			LoadGameInstance->UserIndex = 0;
			LoadGameInstance->Money = 0;
			UGameplayStatics::SaveGameToSlot(LoadGameInstance, LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex);
		}
	}

	//스텟 초기화부분
	PlayerStats.CriticalChance += (LoadGameInstance->CriChanceGrade * PlayerStats.AddCriChance);
	PlayerStats.CriticalDamage += (LoadGameInstance->CriDamageGrade * PlayerStats.AddCriDamage);
	PlayerStats.Def += (LoadGameInstance->DefGrade * PlayerStats.AddDef);
	PlayerStats.AttackDamage += (LoadGameInstance->DamageGrade * PlayerStats.AddDamage);
	PlayerStats.PlayerSpeed += (LoadGameInstance->SpeedGrade * PlayerStats.AddSpeed);
	PlayerStats.MaxHealth += (LoadGameInstance->HealthGrade * PlayerStats.AddHealth);
	PlayerStats.Health += (LoadGameInstance->HealthGrade * PlayerStats.AddHealth);
	
	PlayerStats.ReloadingSpeed += (LoadGameInstance->ReloadGrade * PlayerStats.AddReload);

	PlayerStats.WeaponNumber = LoadGameInstance->UseWeapon;

	GetCharacterMovement()->MaxWalkSpeed = PlayerStats.PlayerSpeed;

	switch (PlayerStats.WeaponNumber) {
		case 0:
			AttachWeapon(Weapon);
			AttachWeapon3DMesh(Weapon);
			break;
		case 1:
			AttachWeapon(SecondWeapon);
			AttachWeapon3DMesh(SecondWeapon);
			break;
		case 2:
			AttachWeapon(ThirdWeapon);
			AttachWeapon3DMesh(ThirdWeapon);
			break;
		default:
			AttachWeapon(Weapon);
			AttachWeapon3DMesh(Weapon);
			break;
	}
	GetWeapon()->SetAmmoCount(GetWeapon()->GetAmmoCount() + (LoadGameInstance->AmmoGrade * PlayerStats.AddAmmo));
	ThirdEquippWeapon->SetActorHiddenInGame(false);
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
			
		}
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
	}

	
	
	
}

void APlayerCharacter::AttachWeapon(TSubclassOf<class AWeaponBase> weapon)
{

	if (weapon && Mesh1P)
	{
		// SpawnActor를 통해 weapon 데이터를 기반으로 한 액터 생성
		EquipWeapon = GetWorld()->SpawnActor<AWeaponBase>(weapon);
		EquipWeapon->mapping(this);

		if (EquipWeapon)
		{
			if (GetWeaponType() == 2) {//만약 핸드건이면
				const USkeletalMeshSocket* WeaponSocket = Mesh1P->GetSocketByName("HandGunGripPoint"); 
				if (WeaponSocket) {
					EquipWeapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, "HandGunGripPoint");
				}
			}
			else {//아니라면

				// 소켓을 찾습니다.
				const USkeletalMeshSocket* WeaponSocket = Mesh1P->GetSocketByName("GripPoint");
				if (WeaponSocket) {
					EquipWeapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, "GripPoint");
				}
			}
			
		}
		UE_LOG(LogTemp, Log, TEXT("Attached : 1"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Not Equipped : 2"));
	}
	UE_LOG(LogTemp, Log, TEXT("Attach end! : 3"));
}

void APlayerCharacter::AttachWeapon3DMesh(TSubclassOf<class AWeaponBase> weapon)
{
	if (weapon && GetMesh())
	{
		ThirdEquippWeapon = GetWorld()->SpawnActor<AWeaponBase>(weapon);

		if (ThirdEquippWeapon)
		{
			const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName("GripPoint"); // 적절한 소켓 이름으로 변경
			if (WeaponSocket)
			{
				ThirdEquippWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "GripPoint");
				UE_LOG(LogTemp, Log, TEXT("Weapon attached to 3rd person mesh."));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Socket not found on 3rd person mesh."));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to spawn weapon."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid weapon or 3rd person mesh."));
	}
}

void APlayerCharacter::WeaponUpgrade()
{
	
	EquipWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	EquipWeapon->Destroy(); // 기존 무기를 제거합니다.
	EquipWeapon = nullptr;

	AttachWeapon(SecondWeapon);

}

void APlayerCharacter::Debuging()
{
	UE_LOG(LogTemp, Log, TEXT("Debug MaxHealth : %f"), PlayerStats.MaxHealth);
	UE_LOG(LogTemp, Log, TEXT("Debug Health : %f"), PlayerStats.Health);
	UE_LOG(LogTemp, Log, TEXT("Debug AttackDamage : %f"), PlayerStats.AttackDamage);
	UE_LOG(LogTemp, Log, TEXT("Debug PlayerSpeed : %f"), PlayerStats.PlayerSpeed);
	UE_LOG(LogTemp, Log, TEXT("Debug Def : %f"), PlayerStats.Def);
	UE_LOG(LogTemp, Log, TEXT("Debug AddOn : %d"), PlayerStats.addOn);
	UE_LOG(LogTemp, Log, TEXT("Debug Reload : %f"), PlayerStats.ReloadingSpeed);
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::StartRun()
{
	GetCharacterMovement()->MaxWalkSpeed *= 1.5;
}

void APlayerCharacter::StopRun()
{
	GetCharacterMovement()->MaxWalkSpeed = PlayerStats.PlayerSpeed;
}

void APlayerCharacter::ShowStat()
{
	if (ABasePlayerController* PController = Cast<ABasePlayerController>(GetController())) {
		PController->GetInstance()->ShowStatBar(this);
	}
}

void APlayerCharacter::ShowEsc()
{
	if (ABasePlayerController* PController = Cast<ABasePlayerController>(GetController())) {
		PController->GetInstance()->ShowEscMenu();
	}
}

void APlayerCharacter::ChangeView()
{
	if (bIsFirstPerson)
	{
		// 부드럽게 세 번째 시점으로 전환합니다.
		FirstPersonCameraComponent->Deactivate();
		ThirdPersonCameraComponent->Activate();

		// 부드러운 전환을 위해 메시 가시성 설정
		Mesh1P->SetVisibility(false);
		GetMesh()->SetVisibility(true);

		// 1인칭에서 3인칭으로 전환할 때 1인칭 캐릭터가 들고있는 무기를 보이지 않게 처리
		if (EquipWeapon)
		{
			EquipWeapon->SetActorHiddenInGame(true);
			ThirdEquippWeapon->SetActorHiddenInGame(false);
		}

		bIsFirstPerson = false;
	}
	else
	{
		// 부드럽게 1인칭 시점으로 전환합니다.
		ThirdPersonCameraComponent->Deactivate();
		FirstPersonCameraComponent->Activate();
		Mesh1P->SetVisibility(true);
		GetMesh()->SetVisibility(false);
		// 1인칭 시점으로 전환할 때도 카메라 위치 및 회전을 보간합니다. 3인칭에서 1인칭으로 전환할 때 1인칭 캐릭터가 들고있는 무기를 보이게 처리
		if (EquipWeapon)
		{
			EquipWeapon->SetActorHiddenInGame(false);
			ThirdEquippWeapon->SetActorHiddenInGame(true);
		}
		bIsFirstPerson = true;
	}
}

int APlayerCharacter::GetMoney()
{
	return PlayerStats.Money;

}

void APlayerCharacter::DeathEvent()
{
	
	FirstPersonCameraComponent->Deactivate();

	DeadCameraComponent->Activate();

	// 부드러운 전환을 위해 메시 가시성 설정
	Mesh1P->SetVisibility(false);
	GetMesh()->SetVisibility(true);

	// 1인칭에서 3인칭으로 전환할 때 1인칭 캐릭터가 들고있는 무기를 보이지 않게 처리
	if (EquipWeapon)
	{
		EquipWeapon->SetActorHiddenInGame(true);
		ThirdEquippWeapon->SetActorHiddenInGame(false);
	}

	if (DeadAnimation) {
		AnimInstance = GetMesh()->GetAnimInstance();
		
		PlayAnimMontage(DeadAnimation);
	}
	
}

void APlayerCharacter::UpdateMoney(float Mount)
{
	PlayerStats.Money += Mount;
}

int APlayerCharacter::GetWeaponType()
{
	return GetWeapon()->GetWeaponType();;
}

void APlayerCharacter::PlayFireAnimation(UAnimMontage* FireAnimation)
{
	AnimInstance = GetMesh1P()->GetAnimInstance();
	AnimInstance->Montage_Play(FireAnimation, 1.0f);
	
}

void APlayerCharacter::PlayMontage(UAnimMontage* PlayAnimation, float Speed)
{
	AnimInstance = GetMesh1P()->GetAnimInstance();
	
	AnimInstance->Montage_Play(PlayAnimation, Speed);
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Running
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &APlayerCharacter::StartRun);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopRun);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		//시점변경
		EnhancedInputComponent->BindAction(ChangeSight, ETriggerEvent::Triggered, this, &APlayerCharacter::ChangeView);
		EnhancedInputComponent->BindAction(DebugKey, ETriggerEvent::Triggered, this, &APlayerCharacter::Debuging);

		//UI관련
		EnhancedInputComponent->BindAction(ShowStatAction, ETriggerEvent::Triggered, this, &APlayerCharacter::ShowStat);
		EnhancedInputComponent->BindAction(EscAction, ETriggerEvent::Triggered, this, &APlayerCharacter::ShowEsc);
	}
	else
	{
	}
}



void APlayerCharacter::ApplyDamage(float Damage)
{
	Damage *= (100.f - PlayerStats.Def)/100.0f;
	// 데미지 적용 후 새로운 체력 값 계산
	float NewHealth = FMath::Max(0.0f, PlayerStats.Health - Damage);

	// 새로운 체력 값 설정
	PlayerStats.Health = NewHealth;
	UE_LOG(LogTemp, Log, TEXT("Hp %f"), PlayerStats.Health);
	if (ABasePlayerController* BaseController = Cast<ABasePlayerController>(GetController()))
	{
		
		if (BaseController->GetInstance())
		{
			BaseController->GetInstance()->UpdateHealth(PlayerStats.Health/ PlayerStats.MaxHealth);
		}
		if (ApplySound) {
			UGameplayStatics::PlaySoundAtLocation(this, ApplySound, GetActorLocation());
		}

		if (PlayerStats.Health <= 0.0f && !Ondead) {
			BaseController->Ondead();
			Ondead = true;
		}
	}
	
}

void APlayerCharacter::UpdateExp(float plusExp)
{
	PlayerStats.Exp += plusExp;

	if (ABasePlayerController* BaseController = Cast<ABasePlayerController>(GetController()))
	{
		if (BaseController->GetInstance())
		{
			if (PlayerStats.Exp >= PlayerStats.MaxExp) {
				//레벨업 게임정지
				BaseController->GetInstance()->UpdateExp(1.0f);
				BaseController->ArgumentStart();
				PlayerStats.Exp = 0;
				if (PlayerStats.MaxExp * 2 >= 0) {
					PlayerStats.MaxExp *= 2;
				}
				
				BaseController->GetInstance()->UpdateExp(0.0f);
			}
			else {
				BaseController->GetInstance()->UpdateExp(PlayerStats.Exp/ PlayerStats.MaxExp);
			}
			
		}
	}

	
}

