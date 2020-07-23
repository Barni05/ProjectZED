// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTZED_API AFPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnCharacterDeath();
private:
	
};
