// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

class UWidgetComponent;
class UHealthComponent;
class USphereComponent;
class UText3DComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS()
class DAY2_ADVANCED_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
	float damage = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
	float shootCooldown = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
	float range = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
	float turretLifeTime = 10.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* turretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UHealthComponent* health;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* DetectionSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UText3DComponent* healthText;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDeath OnDeath;

private:
	float lastShotTime = 0.0f;
	void attackEnemy(AActor* enemy);
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnHealthUpdated(float newHP);
	UFUNCTION()
	void Die();
	UPROPERTY()
	TArray<AActor*> EnemiesInRange;
	




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
