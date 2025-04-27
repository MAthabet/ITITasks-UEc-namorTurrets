// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Containers/Set.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InvsWomanAppilty.generated.h"

class USphereComponent;
class UHealthComponent;

UCLASS()
class DAY2_ADVANCED_API AInvsWomanAppilty : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInvsWomanAppilty();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Affector")
	float Affector = 7.f;
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
private:
	UPROPERTY()
	TSet<UHealthComponent*> ActorsInRange;



};
