// Fill out your copyright notice in the Description page of Project Settings.


#include "InvsWomanAppilty.h"
#include "Components/SphereComponent.h"
#include "Components/HealthComponent.h"

// Sets default values
AInvsWomanAppilty::AInvsWomanAppilty()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
}

// Called when the game starts or when spawned
void AInvsWomanAppilty::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AInvsWomanAppilty::OnOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AInvsWomanAppilty::OnOverlapEnd);
}

// Called every frame
void AInvsWomanAppilty::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (auto& Actor : ActorsInRange)
	{
		if (Actor)
		{
			Actor->changeHealth(Affector * DeltaTime);
		}
	}

}

void AInvsWomanAppilty::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		UHealthComponent* HealthComponent = Cast<UHealthComponent>(OtherActor->GetComponentByClass(UHealthComponent::StaticClass()));
		if (HealthComponent)
		{
			ActorsInRange.Add(HealthComponent);
		}
	}
}

void AInvsWomanAppilty::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("End Overlap with %s"), *OtherActor->GetName());
	if (OtherActor)
	{
		UHealthComponent* HealthComponent = Cast<UHealthComponent>(OtherActor->GetComponentByClass(UHealthComponent::StaticClass()));
		if (HealthComponent)
		{
			ActorsInRange.Remove(HealthComponent);
		}
	}
}



