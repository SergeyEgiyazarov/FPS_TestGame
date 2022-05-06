// Fill out your copyright notice in the Description page of Project Settings.

#include "Challange/FPSLaunchPad.h"
#include "Components/BoxComponent.h"
#include "FPS_TestGame/FPS_TestGameCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
	PrimaryActorTick.bCanEverTick = false;

	OverlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComponent"));
	OverlapComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetRootComponent(OverlapComponent);

	LaunchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaunchMesh"));
	LaunchMesh->SetupAttachment(OverlapComponent);

	ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMesh"));
	ArrowMesh->SetupAttachment(OverlapComponent);

	OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::AddLaunch);
}

void AFPSLaunchPad::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSLaunchPad::AddLaunch(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FVector LaunchVector = GetActorForwardVector() + FVector::UpVector;

	AFPS_TestGameCharacter* MyCharacter = Cast<AFPS_TestGameCharacter>(OtherActor);
	if (MyCharacter)
	{
		MyCharacter->LaunchCharacter(LaunchVector * LaunchStrength, true, true);
		PlayEffect(OtherActor);
		return;
	}
	else if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulse(LaunchVector * LaunchStrength, NAME_None, true);
		PlayEffect(OtherActor);
	}
}

void AFPSLaunchPad::PlayEffect(AActor* OtherActor)
{
	if (!ParticleEffect && !OtherActor) return;
	UGameplayStatics::SpawnEmitterAtLocation(this, ParticleEffect, OtherActor->GetActorLocation());
}
