// Fill out your copyright notice in the Description page of Project Settings.


#include "Pistol.h"

APistol::APistol()
{
	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Gun"));

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(FName("Muzzle Location"));
	MuzzleLocation->SetupAttachment(RootComponent);
}

void APistol::BeginPlay()
{
	Super::BeginPlay();
}

void APistol::OnFire()
{
	UE_LOG(LogTemp, Warning, TEXT("DONKEY: Fire"))
}