// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSExtractionZone.generated.h"

class UBoxComponent;

UCLASS()
class FPS_TESTGAME_API AFPSExtractionZone : public AActor
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	AFPSExtractionZone();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UBoxComponent* OverlapComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* ObjectiveMissingSound;

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
