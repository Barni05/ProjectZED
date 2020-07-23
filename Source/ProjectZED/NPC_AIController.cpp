// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_AIController.h"
#include "Perception/AIPerceptionComponent.h"

ANPC_AIController::ANPC_AIController()
{

}

void ANPC_AIController::BeginPlay()
{
	Super::BeginPlay();
}

void ANPC_AIController::OnNPCDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("DED AI"))
	GetPawn()->DetachFromControllerPendingDestroy();
}