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
	EnableInput(GetWorld()->GetFirstPlayerController());
	InputComponent->BindAction(FName("Fire"), IE_Pressed, this, &APistol::OnFire);
}

void APistol::OnFire()
{
	UE_LOG(LogTemp, Warning, TEXT("DONKEY: Fire"))
}