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
	UPROPERTY(EditAnywhere, Category = "Components")
	class USkeletalMeshComponent* GunMesh;


	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ProjectileSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	FHitResult ShootingHitResult;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float PistolDamage = 30;

private:
	float BulletSpread = 500;
	void LineTrace(class AFPCharacter* PlayerCharacter);

	void ApplyLineTraceDamage();

};
