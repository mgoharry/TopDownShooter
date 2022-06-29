// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthPickUpsSpawner.generated.h"

UCLASS()
class TOPDOWNSHOOTER_API AHealthPickUpsSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthPickUpsSpawner();

	void SpawnHealth();
	void DestroyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:


	UPROPERTY(EditInstanceOnly)
		TArray<AActor*> SpawnPoints;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Pickup;

	UPROPERTY(EditAnywhere)
		float RestartDelay = 5.f;

	FTimerHandle SpawnTimer;
	FTimerHandle DestroyTimer;

	AActor* PickupActor;
};
