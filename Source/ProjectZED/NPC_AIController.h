// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPC_AIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTZED_API ANPC_AIController : public AAIController
{
	GENERATED_BODY()
		ANPC_AIController();

public:
	virtual void BeginPlay() override;

protected:
	
};
