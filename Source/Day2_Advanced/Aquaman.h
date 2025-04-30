// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Aquaman.generated.h"

class UHealthComponent;
class UInputMappingContext;
class UInputAction;
class UInputComponent;
class USpringArmComponent;
class UCameraComponent;
class ATurret;
class UText3DComponent;

UCLASS()
class DAY2_ADVANCED_API AAquaman : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAquaman();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
	int MaxTurrets = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
	float maxShootDist = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
	TSubclassOf<ATurret> turretClass;
	UPROPERTY(EditAnywhere, Category = "Turret")
	USoundBase* turretBuildSound;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "player")
	float currentSpeed = 0.0f;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "player")
	bool isShooting = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TSubclassOf<UAnimInstance> AnimBP;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UHealthComponent* health;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* springArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UText3DComponent* healthText;


	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* IMC;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* ShootAction;


	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHealthUpdated(float newHP);
	UFUNCTION()
	void move(const FInputActionValue& Value);
	UFUNCTION()
	void look(const FInputActionValue& Value);
	UFUNCTION()
	void buildTurret(const FInputActionValue& Value);
	UFUNCTION()
	void turretDie();
	UFUNCTION()
	void changeShootingState();


	UPROPERTY()
	APlayerController* PlayerController;
	UPROPERTY()
	float currentTurrets = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
