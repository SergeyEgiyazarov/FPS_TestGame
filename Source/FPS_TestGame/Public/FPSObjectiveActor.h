// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"

class USphereComponent;

UCLASS()
class FPS_TESTGAME_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	AFPSObjectiveActor();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* PickupFX;

	virtual void BeginPlay() override;

	void PlayEffects();

public:

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
