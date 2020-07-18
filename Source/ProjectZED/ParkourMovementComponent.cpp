
// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TimerManager.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UParkourMovementComponent::UParkourMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UParkourMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	if(GetOwner()->GetInstigatorController()->GetPawn()->IsPlayerControlled())
	{
		GetOwner()->InputComponent->BindAction(FName("Dash"), IE_Pressed, this, &UParkourMovementComponent::Dash);
	}
	PlayerCharacter = Cast<ACharacter>(GetOwner());
}


// Called every frame
void UParkourMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UParkourMovementComponent::Dash()
{
	if (bCanDash == false) { return; }
	bCanDash = false;
	auto Camera = GetOwner()->FindComponentByClass<UCameraComponent>();
	if (!Camera) { return; }
	FVector LaunchVelocity = (Camera->GetForwardVector()) * 20000;
	LaunchVelocity.Z = 0;
	PlayerCharacter->LaunchCharacter(LaunchVelocity, true, true);
	FTimerHandle DashStopHandle;
	FTimerDelegate DashStopDelegate;
	DashStopDelegate.BindUFunction(this, FName("StopDashing"), LaunchVelocity);
	GetWorld()->GetTimerManager().SetTimer(DashStopHandle, DashStopDelegate, 0.1, false);
	GetWorld()->GetTimerManager().SetTimer(DashTimerHandle, this, &UParkourMovementComponent::EnableCanDash, DashCooldown, false);
}

void UParkourMovementComponent::EnableCanDash()
{
	this->bCanDash = true;
}

FTimerHandle UParkourMovementComponent::GetDashTimerHandle() const
{
	return DashTimerHandle;
}

void UParkourMovementComponent::StopDashing(FVector LaunchVelocity)
{
	PlayerCharacter->GetMovementComponent()->StopMovementImmediately();
}