// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;

UCLASS()
class FPS_TESTGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:

	AFPSAIGuard();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UPawnSensingComponent* PawnSensingComp;

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
};
