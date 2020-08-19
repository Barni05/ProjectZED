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
	PlacePlayerGun();
	PlaceNormalGun();
	PlayerGun = GetCurrentGun();
	if (!PlayerGun) { return; }
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
		if (CurrentAttachedActor->ActorHasTag(FName("Gun")) && !CurrentAttachedActor->ActorHasTag(FName("Not Visible to Player")))
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

void AFPCharacter::PlacePlayerGun()
{
	PlayerGun = GetWorld()->SpawnActor<AGun>(GunBlueprint, FVector(0, 0, 0), FRotator(0, -90, 0));
	PlayerGun->AttachToComponent(FPCamera, FAttachmentTransformRules::KeepRelativeTransform);
	PlayerGun->SetOwner(this);
	PlayerGun->Tags.Add(FName("Player Gun"));
}

void AFPCharacter::PlaceNormalGun()
{
	NormalGun = GetWorld()->SpawnActor<AGun>(GunBlueprint);
	NormalGun->Tags.Add(FName("Not Visible to Player"));
	NormalGun->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform, FName("GripPoint"));
	NormalGun->SetOwner(this);
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