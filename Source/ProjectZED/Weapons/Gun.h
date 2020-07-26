// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.h"
#include "Gun.generated.h"

UCLASS()
class PROJECTZED_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AGun> GunBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	class TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(VisibleAnywhere, Category = "Firing")
	float CrosshairXLocation = 0.5;
	UPROPERTY(VisibleAnywhere, Category = "Firing")
	float CrosshairYLocation = 0.5;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
