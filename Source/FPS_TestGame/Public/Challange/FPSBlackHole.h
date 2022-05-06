// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBlackHole.generated.h"

class USphereComponent;

UCLASS()
class FPS_TESTGAME_API AFPSBlackHole : public AActor
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	AFPSBlackHole();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* ExternalSphere;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* IternalSphere;

	virtual void BeginPlay() override;

	UFUNCTION()
	void IternalSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
