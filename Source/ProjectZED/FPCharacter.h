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


protected:

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UStaticMeshComponent* Mesh1P;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UCameraComponent* FPCamera;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class USpringArmComponent* CameraBoom;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* Gun;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
