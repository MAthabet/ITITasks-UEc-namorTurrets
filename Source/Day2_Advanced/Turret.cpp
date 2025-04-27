// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Components/HealthComponent.h"
#include "Components/SphereComponent.h"
#include "C:\Program Files\Epic Games\UE_5.4\Engine\Plugins\Experimental\Text3D\Source\Text3D\Public\Text3DComponent.h"


// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	turretMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TurretMesh"));
	turretMesh->SetupAttachment(RootComponent);

	health = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	health->OnHealthChanged.AddDynamic(this, &ATurret::OnHealthUpdated);

	healthText = CreateDefaultSubobject<UText3DComponent>(TEXT("HealthText"));
	healthText->SetupAttachment(turretMesh);

	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	DetectionSphere->SetupAttachment(turretMesh);
	DetectionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DetectionSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	DetectionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}


void ATurret::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (OtherActor->ActorHasTag(TEXT("Enemy")))
		{
			EnemiesInRange.Add(OtherActor);
			if(EnemiesInRange.Num() == 1)
				attackEnemy(OtherActor);
		}
		else
		{
			return;
		}
	}
	
}

void ATurret::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		if (OtherActor->ActorHasTag(TEXT("Enemy")))
		{
			EnemiesInRange.Remove(OtherActor);
			if (EnemiesInRange.Num() > 0)
				attackEnemy(EnemiesInRange[0]);
		}
		else
		{
			return;
		}
	}
}

void ATurret::OnHealthUpdated(float newHP)
{
	if (newHP <= 0)
		Die();
	else if (healthText)
	{
		FString healthString = FString::Printf(TEXT("Health: %d"), FMath::RoundToInt(newHP));
		healthText->SetText(FText::FromString(healthString));
	}
}

void ATurret::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("Turret is dead"));
	OnDeath.Broadcast();
	this->Destroy();	
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();

	//die after time
	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &ATurret::Die, turretLifeTime, false);

	if (DetectionSphere)
	{
		DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &ATurret::OnOverlapBegin);
		DetectionSphere->OnComponentEndOverlap.AddDynamic(this, &ATurret::OnOverlapEnd);
		DetectionSphere->SetSphereRadius(range);
	}

}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurret::attackEnemy(AActor* enemy)
{
	if (enemy)
	{
		if (lastShotTime + shootCooldown < GetWorld()->GetTimeSeconds())
		{
			lastShotTime = GetWorld()->GetTimeSeconds();
			FVector start = this->GetActorLocation();
			FVector end = enemy->GetActorLocation();
			FHitResult hitResult;
			if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECC_Visibility))
			{
				if (hitResult.GetActor() == enemy)
				{
					UHealthComponent* healthComp = Cast<UHealthComponent>(enemy->GetComponentByClass(UHealthComponent::StaticClass()));
					if (healthComp)
					{
						healthComp->changeHealth(-damage);
					}
				}
			}
		}
	}
	else
		EnemiesInRange.Remove(enemy);
	if (EnemiesInRange.Num() > 0)
		attackEnemy(EnemiesInRange[0]);
}
