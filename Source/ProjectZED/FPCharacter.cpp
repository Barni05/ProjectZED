// Fill out your copyright notice in the Description page of Project Settings.


#include "FPCharacter.h"
#include "Camera/CameraComponent.h"
#include <typeinfo>
#include "Weapons/Gun.h"
#include "Weapons/Pistol.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AFPCharacter::AFPCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 0;
	CameraBoom->SetRelativeLocation(FVector(0, 0, 0));

	FPCamera = CreateDefaultSubobject<UCameraComponent>(FName("FPCamera"));
	FPCamera->SetupAttachment(CameraBoom);
	FPCamera->SetRelativeLocation(FVector(0, 0, 30));

	Mesh1P = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh1P"));
	Mesh1P->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AFPCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlaceGun();

}

// Called every frame
void AFPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPCharacter::PlaceGun()
{
	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);
	Gun->AttachToComponent(FPCamera, FAttachmentTransformRules::SnapToTargetIncludingScale);
	Gun->SetActorRelativeLocation(FVector(60, 30, -30));
	Gun->SetActorRelativeRotation(FRotator(0, -90, 0));
	Gun->SetActorRelativeScale3D(FVector(0.1, 0.1, 0.1));
}

// Called to bind functionality to input
void AFPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(FName("Fire"), EInputEvent::IE_Pressed, this, &AFPCharacter::Fire);
}

void AFPCharacter::Fire()
{
	OnFire(GunBlueprint);
}

void AFPCharacter::OnFire(TSubclassOf<APistol> PistolBlueprint)
{
	auto Pistol = Cast<APistol>(Gun);
	if (!Pistol) { return; }
	Pistol->OnFire();
}

void AFPCharacter::OnFire(TSubclassOf<AGun> GunBP)
{
	UE_LOG(LogTemp, Warning, TEXT("DONKEY: ONFire FPCharacter.cpp"))
}

void AFPCharacter::SetGun(TSubclassOf<AActor> GunRef)
{
	GunBlueprint = GunRef;
}