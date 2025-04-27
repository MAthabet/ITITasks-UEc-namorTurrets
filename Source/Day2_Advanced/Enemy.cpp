// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "C:\Program Files\Epic Games\UE_5.4\Engine\Plugins\Experimental\Text3D\Source\Text3D\Public\Text3DComponent.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	health = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	health->OnHealthChanged.AddDynamic(this, &AEnemy::OnHealthUpdated);

	enemyCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("EnemyCollision"));
	enemyCollision->SetupAttachment(RootComponent);
	enemyCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);


	enemyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnemyMesh"));
	enemyMesh->SetupAttachment(enemyCollision);


	healthText = CreateDefaultSubobject<UText3DComponent>(TEXT("HealthText"));
	healthText->SetupAttachment(enemyMesh);


	Tags.Add(FName("Enemy"));

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::OnHealthUpdated(float newHP)
{
	if (newHP <= 0)
	{
		isDead = true;
		if (enemyMesh)
		{
			enemyMesh->SetSimulatePhysics(true);
			enemyMesh->SetCollisionProfileName(TEXT("Ragdoll"));
		}
		SetLifeSpan(3.0f);
	}
	else if (healthText)
	{
		FString healthString = FString::Printf(TEXT("HP: %d"), FMath::RoundToInt(newHP));
		healthText->SetText(FText::FromString(healthString));
	}
}
