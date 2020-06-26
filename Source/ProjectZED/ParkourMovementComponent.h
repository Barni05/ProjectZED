// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ParkourMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTZED_API UParkourMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UParkourMovementComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void EnableCanDash();

	UFUNCTION(BlueprintCallable, Category = "Timers")
	FTimerHandle GetDashTimerHandle() const;


	UPROPERTY(EditAnywhere, Category = "Setup")
	float DashCooldown = 5;


	UPROPERTY(EditAnywhere, Category = "Setup")
	bool bCanDash = true;

	ACharacter* PlayerCharacter;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	FTimerHandle DashTimerHandle;

	void Dash();

	UFUNCTION()
	void StopDashing(FVector LaunchVelocity);


		
};
