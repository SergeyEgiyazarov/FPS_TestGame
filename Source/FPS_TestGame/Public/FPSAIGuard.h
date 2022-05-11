// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EGuardState : uint8
{
	Idle,
	Suspicious,
	Alerted,
};

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

	UFUNCTION()
	void OnPawnSeen(APawn* SeePawn);

	UFUNCTION()
	void OnNoiseHear(APawn* NoiseInstigator, const FVector& Location, float Volume);

	FRotator OriginalRotation;

	FTimerHandle TimerHandel_ResetOriginalRotation;

	EGuardState CurrentState;

	void SetGuardState(EGuardState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnStateChange(EGuardState NewState);

	UFUNCTION()
	void ResetOriginalRotation();

public:

	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditInstanceOnly, Category = "Patrol")
	bool bPatrol = false;

	UPROPERTY(EditInstanceOnly, Category = "Patrol")
	AActor* FirstPatrolPoint;

	UPROPERTY(EditInstanceOnly, Category = "Patrol")
	AActor* SecondPatrolPoint;

	AActor* CurrentPatrolPoint;

	void MoveToNextPatrolPoint();
};
