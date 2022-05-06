// Fill out your copyright notice in the Description page of Project Settings.

#include "Challange/FPSBlackHole.h"
#include "Components/SphereComponent.h"

// Sets default values
AFPSBlackHole::AFPSBlackHole()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(Mesh);

	ExternalSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ExternalSphere"));
	ExternalSphere->SetupAttachment(Mesh);
	ExternalSphere->SetSphereRadius(1500.0f);

	IternalSphere = CreateDefaultSubobject<USphereComponent>(TEXT("IternalSphere"));
	IternalSphere->SetupAttachment(Mesh);
	IternalSphere->SetSphereRadius(100.0f);
	IternalSphere->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackHole::IternalSphereOverlap);
}

// Called when the game starts or when spawned
void AFPSBlackHole::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSBlackHole::IternalSphereOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}

// Called every frame
void AFPSBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> OverlapindActors;
	ExternalSphere->GetOverlappingComponents(OverlapindActors);
	auto SphereRadius = ExternalSphere->GetScaledSphereRadius();

	for (auto OverlapActor : OverlapindActors)
	{
		if (OverlapActor->IsSimulatingPhysics())
		{
			OverlapActor->AddRadialForce(GetActorLocation(), SphereRadius, -2000.0f, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}
}
