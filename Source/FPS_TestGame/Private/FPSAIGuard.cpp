// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "FPS_TestGame/FPS_TestGameGameMode.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AFPSAIGuard::AFPSAIGuard()
{
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHear);

	CurrentState = EGuardState::Idle;
}

void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();

	OriginalRotation = GetActorRotation();

	if (bPatrol)
	{
		MoveToNextPatrolPoint();
	}
}

void AFPSAIGuard::OnPawnSeen(APawn* SeePawn)
{
	if (!SeePawn) return;

	DrawDebugSphere(GetWorld(), SeePawn->GetActorLocation(), 32.0f, 12, FColor::Yellow, false, 5.0f);

	SetGuardState(EGuardState::Alerted);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandel_ResetOriginalRotation);

	AFPS_TestGameGameMode* GM = Cast<AFPS_TestGameGameMode>(GetWorld()->GetAuthGameMode());
	if (!GM) return;

	GM->CompleteMission(SeePawn, false);

	AController* GuardController = GetController();
	if (GuardController)
	{
		GuardController->StopMovement();
	}
}

void AFPSAIGuard::OnNoiseHear(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	if (CurrentState == EGuardState::Alerted) return;
	SetGuardState(EGuardState::Suspicious);

	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Red, false, 5.0f);

	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f;
	NewLookAt.Roll = 0.0f;

	SetActorRotation(NewLookAt);

	GetWorld()->GetTimerManager().ClearTimer(TimerHandel_ResetOriginalRotation);
	GetWorld()->GetTimerManager().SetTimer(TimerHandel_ResetOriginalRotation, this, &AFPSAIGuard::ResetOriginalRotation, 3.0f);

	AController* GuardController = GetController();
	if (GuardController)
	{
		GuardController->StopMovement();
	}
}

void AFPSAIGuard::SetGuardState(EGuardState NewState)
{
	if (CurrentState == NewState) return;
	CurrentState = NewState;
	OnStateChange(CurrentState);
}

void AFPSAIGuard::ResetOriginalRotation()
{
	if (CurrentState == EGuardState::Alerted) return;
	SetActorRotation(OriginalRotation);
	SetGuardState(EGuardState::Idle);
	if (bPatrol)
	{
		MoveToNextPatrolPoint();
	}
}

void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentPatrolPoint)
	{
		FVector Delta = GetActorLocation() - CurrentPatrolPoint->GetActorLocation();
		float DistanceToGoal = Delta.Size();
		if (DistanceToGoal < 100)
		{
			MoveToNextPatrolPoint();
		}
	}
}

void AFPSAIGuard::MoveToNextPatrolPoint()
{
	if (CurrentPatrolPoint == nullptr || CurrentPatrolPoint == SecondPatrolPoint)
	{
		CurrentPatrolPoint = FirstPatrolPoint;
	}
	else
	{
		CurrentPatrolPoint = SecondPatrolPoint;
	}

	UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), CurrentPatrolPoint);
}
