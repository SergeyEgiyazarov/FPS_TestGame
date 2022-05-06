// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"

AFPSAIGuard::AFPSAIGuard()
{
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
}

void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
