// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Weapons/Gun.h"
#include "Pistol.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTZED_API APistol : public AGun
{
	GENERATED_BODY()
public:

	APistol();

	void OnFire();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Firing")
	FVector HitLocation;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UStaticMeshComponent* GunMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class USceneComponent* MuzzleLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ProjectileSpeed;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float BulletSpread = 500;

	void LineTrace(class AFPCharacter* PlayerCharacter);
};
