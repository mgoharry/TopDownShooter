// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickUpsSpawner.h"
#include "TimerManager.h"


// Sets default values
AHealthPickUpsSpawner::AHealthPickUpsSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//SpawnHealth();
}

void AHealthPickUpsSpawner::SpawnHealth()
{
	FActorSpawnParameters SpawnParams;
	int Rando = FMath::RandRange(0,3);
	PickupActor = GetWorld()->SpawnActor<AActor>(Pickup, SpawnPoints[Rando]->GetActorLocation(), SpawnPoints[Rando]->GetActorRotation(), SpawnParams);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AHealthPickUpsSpawner::SpawnHealth, RestartDelay);
	GetWorldTimerManager().SetTimer(DestroyTimer, this, &AHealthPickUpsSpawner::DestroyActor, RestartDelay);
}

void AHealthPickUpsSpawner::DestroyActor()
{
	PickupActor->Destroy();
}

// Called when the game starts or when spawned
void AHealthPickUpsSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnHealth();
	
}

// Called every frame
void AHealthPickUpsSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

