// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPCharacter.generated.h"

UCLASS()
class PROJECTZED_API AFPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPCharacter();

	class AGun* Gun;

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	TSubclassOf<AGun> GunBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UCameraComponent* FPCamera;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UStaticMeshComponent* Mesh1P;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class USpringArmComponent* CameraBoom;
	
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void PlaceGun();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void SetGun(TSubclassOf<AActor> GunRef);

	AGun* GetCurrentGun();
};
