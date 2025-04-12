#include "collider.h"
#include "Components/SphereComponent.h"
#include "Engine/Engine.h"

USphereComponent* SphereCollision;
Acollider::Acollider()
{
	PrimaryActorTick.bCanEverTick = true;

	addSCollider();
}

void Acollider::addSCollider()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = SphereCollision;
	SphereCollision->SetSphereRadius(100.0f);
	SphereCollision->SetGenerateOverlapEvents(true);
}

void Acollider::BeginPlay()
{
	Super::BeginPlay();
	
	// Bind the overlap functions
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &Acollider::OnOverlapBegin);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &Acollider::OnOverlapEnd);
}

void Acollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void Acollider::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Enter"));
	}
}

void Acollider::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Exit"));
	}
}
