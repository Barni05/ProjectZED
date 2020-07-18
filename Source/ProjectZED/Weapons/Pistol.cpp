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
	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Gun"));
	RootComponent = GunMesh;

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(FName("Muzzle Location"));
	MuzzleLocation->AttachTo(RootComponent);
}

void APistol::BeginPlay()
{
	Super::BeginPlay();
	EnableInput(GetWorld()->GetFirstPlayerController());
	InputComponent->BindAction(FName("Fire"), IE_Pressed, this, &APistol::OnFire);
}

void APistol::OnFire()
{
	auto PlayerCharacter = Cast<AFPCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (!PlayerCharacter) { return; }
	LineTrace(PlayerCharacter);

}

void APistol::LineTrace(AFPCharacter* PlayerCharacter)
{
	//Camera Trace
	auto ForwardVector = PlayerCharacter->FPCamera->GetForwardVector();
	auto WorldLocation = ActorToWorld().TransformPosition(PlayerCharacter->FPCamera->GetRelativeLocation());
	FHitResult CameraHitResult;
	float NegativeSpread = BulletSpread * -1;
	FVector SpreadOffset = FVector(FMath::FRandRange(NegativeSpread, BulletSpread), FMath::FRandRange(NegativeSpread, BulletSpread), FMath::FRandRange(NegativeSpread, BulletSpread));
	FVector CameraEndLocation = ForwardVector * 20000 + WorldLocation + SpreadOffset;
	bool bCameraHit = GetWorld()->LineTraceSingleByChannel(CameraHitResult, WorldLocation, CameraEndLocation, ECollisionChannel::ECC_Visibility);
	HitLocation = CameraHitResult.ImpactPoint;
}
