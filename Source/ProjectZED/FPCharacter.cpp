// Fill out your copyright notice in the Description page of Project Settings.


#include "FPCharacter.h"
#include "Camera/CameraComponent.h"
#include <typeinfo>
#include "Weapons/Gun.h"
#include "Weapons/Pistol.h"
#include "FPPlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "NPC_AIController.h"
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

}

// Called when the game starts or when spawned
void AFPCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlaceGun();
	Gun = GetCurrentGun();
	if (!Gun) { return; }
}

float AFPCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	FMath::Clamp<float>(DamageAmount, 0, StartingHealth);
	Health -= DamageAmount;
	if (Health <= 0)
	{
		DetachControllers();
	}
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health)
	return DamageAmount;
}

AGun* AFPCharacter::GetCurrentGun()
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	for (AActor* CurrentAttachedActor : AttachedActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("La Gun: %s"), *CurrentAttachedActor->GetName())
		if (CurrentAttachedActor->ActorHasTag(FName("Gun")))
		{
			return Cast<AGun>(CurrentAttachedActor);
		}
		
	}
	return nullptr;
}

// Called every frame
void AFPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPCharacter::DetachControllers()
{
	if (!GetController()) { return; }
	if (GetController()->IsPlayerController())
	{
		auto PlayerController = Cast<AFPPlayerController>(GetController());
		PlayerController->OnCharacterDeath();
	}
	else if (GetController()->IsPlayerController() == false)
	{
		auto AIController = Cast<ANPC_AIController>(GetController());
		AIController->OnNPCDeath();
	}
}

void AFPCharacter::PlaceGun()
{
	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);
	Gun->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	Gun->SetActorRelativeLocation(FVector(-20, 60, -40));
}

// Called to bind functionality to input
void AFPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

void AFPCharacter::SetGun(TSubclassOf<AActor> GunRef)
{
	GunBlueprint = GunRef;
}