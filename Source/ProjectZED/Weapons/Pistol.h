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

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UStaticMeshComponent* GunMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class USceneComponent* MuzzleLocation;
};
