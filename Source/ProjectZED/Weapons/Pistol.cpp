// Fill out your copyright notice in the Description page of Project Settings.


#include "Pistol.h"
#include "Camera/CameraComponent.h"
#include "../FPCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.h"
#include "DrawDebugHelpers.h"

APistol::APistol()
{
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Gun Mesh"));
	SetRootComponent(GunMesh);
}

void APistol::BeginPlay()
{
	Super::BeginPlay();
	EnableInput(GetWorld()->GetFirstPlayerController());
	if (!InputComponent) { return; }
	InputComponent->BindAction(FName("Fire"), IE_Pressed, this, &APistol::OnFire);
}

void APistol::OnFire()
{
	auto PlayerCharacter = Cast<AFPCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (!PlayerCharacter) { return; }
	LineTrace(PlayerCharacter);
	if (CheckValidity(ShootingHitResult.GetActor(), "UEC1: Hit actor not found in Pistol.cpp")) { return; }
	UE_LOG(LogTemp, Warning, TEXT("Actor : %s"), *ShootingHitResult.GetActor()->GetName())

	//Seperate to a funcion --BEGIN
	auto ParentActor = Cast<AFPCharacter>(GetParentActor());
	if (!ParentActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEC2: No parent actor found for %s in Pistol.cpp"), *this)
		return;
	}
	UGameplayStatics::ApplyPointDamage(ShootingHitResult.GetActor(), 20, ShootingHitResult.ImpactNormal, ShootingHitResult, ParentActor->GetController(), this, UDamageType::StaticClass());
	//Seperate to a function --END
}

void APistol::LineTrace(AFPCharacter* PlayerCharacter)
{
	//Camera Trace
	auto ForwardVector = PlayerCharacter->FPCamera->GetForwardVector();
	auto WorldLocation = ActorToWorld().TransformPosition(PlayerCharacter->FPCamera->GetRelativeLocation());
	float NegativeSpread = BulletSpread * -1;
	FVector SpreadOffset = FVector(FMath::FRandRange(NegativeSpread, BulletSpread), FMath::FRandRange(NegativeSpread, BulletSpread), FMath::FRandRange(NegativeSpread, BulletSpread));
	FVector CameraEndLocation = ForwardVector * 20000 + WorldLocation + SpreadOffset;
	bool bCameraHit = GetWorld()->LineTraceSingleByChannel(ShootingHitResult, WorldLocation, CameraEndLocation, ECollisionChannel::ECC_Visibility);
	HitLocation = ShootingHitResult.ImpactPoint;
	if (!bCameraHit)
	{
		HitLocation = CameraEndLocation;
	}
	DrawDebugLine(GetWorld(), WorldLocation, HitLocation, FColor::Blue, false, 10, 0, 10);
}

bool APistol::CheckValidity(UObject* ObjectToCheck, FString ErrorMessage)
{
	if (!ObjectToCheck)
	{
		UE_LOG(LogTemp, Error, TEXT("%s"), *ErrorMessage)
		return true;
	}
	return false;
}