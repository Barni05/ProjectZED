// Fill out your copyright notice in the Description page of Project Settings.


#include "Pistol.h"
#include "Camera/CameraComponent.h"
#include "../FPCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.h"
#include "../FPPlayerController.h"
#include "DrawDebugHelpers.h"

APistol::APistol()
{
}

void APistol::BeginPlay()
{
	Super::BeginPlay();
	EnableInput(GetWorld()->GetFirstPlayerController());
	if (!InputComponent) { return; }
	GunMesh = FindComponentByClass<USkeletalMeshComponent>();
	InputComponent->BindAction(FName("Fire"), IE_Pressed, this, &APistol::OnFire);
}

void APistol::OnFire()
{
	auto PlayerCharacter = Cast<AFPCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (!PlayerCharacter) { return; }
	LineTrace(PlayerCharacter);
	if (!ShootingHitResult.GetActor())
	{
		return;
	}
	ApplyLineTraceDamage();
}

void APistol::ApplyLineTraceDamage()
{
	auto ParentActor = Cast<AFPCharacter>(GetAttachParentActor());
	if (!ParentActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEC2: No parent actor found for %s in Pistol.cpp"), *this->GetName())
			return;
	}
	UGameplayStatics::ApplyPointDamage(ShootingHitResult.GetActor(), PistolDamage, ShootingHitResult.ImpactNormal, ShootingHitResult, ParentActor->GetController(), this, UDamageType::StaticClass());

}

void APistol::LineTrace(AFPCharacter* PlayerCharacter)
{
	int32 ViewportSizeX, ViewportSizeY;
	auto PlayerController = Cast<AFPPlayerController>(PlayerCharacter->GetController());
	PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);
	float ScreenX = ViewportSizeX * CrosshairXLocation;
	float ScreenY = ViewportSizeY * CrosshairYLocation;

	auto ScreenLocation = FVector2D(ScreenX, ScreenY);

	FVector WorldDirection, WorldLocation;
	PlayerController->DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection);	

	//Camera Trace
	auto ForwardVector = PlayerCharacter->FPCamera->GetForwardVector();
	auto CameraLocation = ActorToWorld().TransformPosition(PlayerCharacter->FPCamera->GetRelativeLocation());
	float NegativeSpread = BulletSpread * -1;
	FVector SpreadOffset = FVector(FMath::FRandRange(NegativeSpread, BulletSpread), FMath::FRandRange(NegativeSpread, BulletSpread), FMath::FRandRange(NegativeSpread, BulletSpread));
	FVector CameraEndLocation = WorldDirection * 20000 + CameraLocation + SpreadOffset;
	bool bCameraHit = GetWorld()->LineTraceSingleByChannel(ShootingHitResult, CameraLocation, CameraEndLocation, ECollisionChannel::ECC_Visibility);
	HitLocation = ShootingHitResult.ImpactPoint;
	DrawDebugLine(GetWorld(), CameraLocation, CameraEndLocation, FColor::Cyan, false, 10, 0, 10);
	if (!bCameraHit)
	{
		HitLocation = CameraEndLocation;
	}
}