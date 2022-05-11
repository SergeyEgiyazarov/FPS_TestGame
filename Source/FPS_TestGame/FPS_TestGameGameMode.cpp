// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_TestGameGameMode.h"
#include "FPS_TestGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AFPS_TestGameGameMode::AFPS_TestGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

void AFPS_TestGameGameMode::CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess)
{
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);

		if (!SpectatingViewpointClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass is nullptr. Please update GameMode class with valid subclass. Cannot change spectating view target."));
			return;
		}

		TArray<AActor*> ReturnsActors;
		UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnsActors);

		if (ReturnsActors.Num() > 0)
		{
			AActor* NewViewTarget = ReturnsActors[0];

			APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
			if (!PC) return;

			PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
		}
	}

	OnMissionComplete(InstigatorPawn, bMissionSuccess);
}
