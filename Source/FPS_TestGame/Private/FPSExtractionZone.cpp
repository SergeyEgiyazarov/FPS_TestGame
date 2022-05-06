// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "FPS_TestGame/FPS_TestGameCharacter.h"
#include "FPS_TestGame/FPS_TestGameGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	OverlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComponent"));
	OverlapComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComponent->SetBoxExtent(FVector(100.0f));
	SetRootComponent(OverlapComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(OverlapComponent);

	OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);
}

void AFPSExtractionZone::HandleOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFPS_TestGameCharacter* MyPawn = Cast<AFPS_TestGameCharacter>(OtherActor);
	if (!MyPawn) return;

	if (MyPawn->IsCarryingObjective)
	{
		AFPS_TestGameGameMode* GM = Cast<AFPS_TestGameGameMode>(GetWorld()->GetAuthGameMode());
		if (!GM) return;

		GM->CompleteMission(MyPawn);
	}
	else
	{
		if (!ObjectiveMissingSound) return;
		UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
	}

	UE_LOG(LogTemp, Display, TEXT("Overlap wthis extraction zone!"));
}
