// Fill out your copyright notice in the Description page of Project Settings.


#include "Aquaman.h"
#include "Turret.h"
#include "Components/HealthComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Sound/SoundBase.h" 
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "C:\Program Files\Epic Games\UE_5.4\Engine\Plugins\Experimental\Text3D\Source\Text3D\Public\Text3DComponent.h"


// Sets default values
AAquaman::AAquaman()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	health = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	health->OnHealthChanged.AddDynamic(this, &AAquaman::OnHealthUpdated);

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	springArm->SetupAttachment(RootComponent);
	
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	camera->SetupAttachment(springArm);

	healthText = CreateDefaultSubobject<UText3DComponent>(TEXT("HealthText"));
	healthText->SetupAttachment(RootComponent);

	if (GetMesh())
	{
		GetMesh()->SetAnimInstanceClass(AnimBP);
	}

}

// Called when the game starts or when spawned
void AAquaman::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC, 0);
		}
	}
	
}


// Called every frame
void AAquaman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentSpeed = GetVelocity().Size();

}

// Called to bind functionality to input
void AAquaman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if(MoveAction)
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAquaman::move);
		if (LookAction)
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAquaman::look);
		if (ShootAction)
			EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AAquaman::buildTurret);
	}
}

void AAquaman::OnHealthUpdated(float newHP)
{
	if (newHP <= 0)
	{
		// Handle player death
		UE_LOG(LogTemp, Warning, TEXT("Player is dead"));
	}
	else if (healthText)
	{
		FString healthString = FString::Printf(TEXT("Health: %d"), FMath::RoundToInt(newHP));
		healthText->SetText(FText::FromString(healthString));
	}
}

void AAquaman::move(const FInputActionValue& Value)
{
	FVector2D movement = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), movement.Y);
	AddMovementInput(GetActorRightVector(), movement.X);
}

void AAquaman::look(const FInputActionValue& Value)
{
	FVector2D look = Value.Get<FVector2D>();
	
	if (PlayerController)
	{
		PlayerController->AddYawInput(look.X);
	}
	if (camera)
	{
		FRotator cameraRotation = camera->GetRelativeRotation();
		cameraRotation.Pitch = FMath::Clamp(cameraRotation.Pitch + look.Y, -50.0f, 50.0f);
		camera->SetRelativeRotation(cameraRotation);

	}
}

void AAquaman::buildTurret(const FInputActionValue& Value)
{
	isShooting = 1.0f;

	if (currentTurrets >= MaxTurrets)
	{
		return;
	}
	currentTurrets++;

	FVector start = camera->GetComponentLocation();
	FVector end = start + camera->GetForwardVector() * maxShootDist;
	FHitResult hitResult;
	FCollisionQueryParams collisionParams;
	FVector spawnLocation;
	FRotator spawnRotation;
	collisionParams.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECC_Visibility, collisionParams))
	{
		spawnLocation = hitResult.Location;
		spawnRotation = FRotator::ZeroRotator;
	}
	else
	{
		spawnLocation = end;
		spawnRotation = FRotator::ZeroRotator;
	}
	 ATurret* turret = GetWorld()->SpawnActor<ATurret>(turretClass, spawnLocation, spawnRotation);
	 if (turret)
		 turret->OnDeath.AddDynamic(this, &AAquaman::turretDie);
	 if (turretBuildSound)
	 {
		 UGameplayStatics::PlaySoundAtLocation(this, turretBuildSound, spawnLocation);
	 }
}

void AAquaman::turretDie()
{
	currentTurrets--;
}


