// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSLaunchPad.generated.h"

class UBoxComponent;

UCLASS()
class FPS_TESTGAME_API AFPSLaunchPad : public AActor
{
	GENERATED_BODY()

public:

	AFPSLaunchPad();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UBoxComponent* OverlapComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* LaunchMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* ArrowMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ParticleEffect;

	UPROPERTY(EditAnywhere, Category = "Launch")
	float LaunchStrength = 1500.0f;

	virtual void BeginPlay() override;

public:

	UFUNCTION()
	void AddLaunch(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	void PlayEffect(AActor* OtherActor);
};
