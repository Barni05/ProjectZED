// Fill out your copyright notice in the Description page of Project Settings.


#include "FPPlayerController.h"
#include "FPCharacter.h"

void AFPPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedCharacter = Cast<AFPCharacter>(InPawn);
		if (PossessedCharacter == nullptr) 
		{
			UE_LOG(LogTemp, Warning, TEXT("UEC3: Possessed Character not found in FPPlayerController.cpp"))
			return;
		}
	}
}

void AFPPlayerController::OnCharacterDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("DED"))
	StartSpectatingOnly();
}