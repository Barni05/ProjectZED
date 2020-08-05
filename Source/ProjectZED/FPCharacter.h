// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Delegates/Delegate.h"
#include "CoreMinimal.h"
#include "FPCharacter.generated.h"

UCLASS()
class PROJECTZED_API AFPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPCharacter();

	class AGun* Gun;

	UPROPERTY(EditAnywhere, Category = "Weapons")
	TSubclassOf<AGun> GunBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UCameraComponent* FPCamera;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UStaticMeshComponent* Mesh1P;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class USpringArmComponent* CameraBoom;
	UPROPERTY(EditDefaultsOnly, Category = "Helth")
	float StartingHealth = 100;

	float Health = StartingHealth;
	
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
private:
	void PlaceGun();

	void DetachControllers();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void SetGun(TSubclassOf<AActor> GunRef);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	AGun* GetCurrentGun();
};
