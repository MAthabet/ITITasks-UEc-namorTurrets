// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/HealthComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	health = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	health->OnHealthChanged.AddDynamic(this, &AEnemy::OnHealthUpdated);


	enemyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnemyMesh"));
	enemyMesh->SetupAttachment(RootComponent);
	enemyMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	HealthWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidget"));
	HealthWidget->SetupAttachment(enemyMesh);
	HealthWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidget->SetDrawSize(FVector2D(100, 50));

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

		enemyMesh->SetSimulatePhysics(true);
		enemyMesh->SetCollisionProfileName(TEXT("Ragdoll"));
		SetLifeSpan(3.0f);
	}
	else
	{
		// Update the health widget
		if (HealthWidget)
		{
			UUserWidget* widget = Cast<UUserWidget>(HealthWidget->GetUserWidgetObject());
			if (widget)
			{
				// Assuming you have a function in your widget to update the health bar
				// widget->UpdateHealthBar(newHP);
			}
		}

	}
}
