// Fill out your copyright notice in the Description page of Project Settings.


#include "KillThemAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterPlayerController.h"
#include "EnemyAIController.h"
#include "EnemySpawner.h"
#include "EnemyCharacter.h"


void AKillThemAllGameMode::BeginPlay()
{
	Super::BeginPlay();
	SpawnWave(Wave);

}
void AKillThemAllGameMode::PawnKilled(APawn* PawnKilled) {

	Super::PawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());

	if (PlayerController != nullptr) {

		EndGame(false);
	}

	for (AEnemyAIController* Controller : TActorRange<AEnemyAIController>(GetWorld())) {
		if (!Controller->IsDead()) {
			return;
		}
	}


	
	
	
	if (Wave > 1) {
		EndGame(true);
	}
	else {
		Wave++;
		SpawnWave(Wave);
	}
}

void AKillThemAllGameMode::SpawnWave(int WaveNumber)
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("EnemySpawnPoint"), SpawnPoints);
	if (SpawnPoints.Num() > 0) {
		for (int i = 0; i <= WaveNumber * 2; i++) {
			GetWorld()->SpawnActor<AEnemyCharacter>(Enemy, SpawnPoints[i]->GetActorLocation(), SpawnPoints[i]->GetActorRotation());
		}
	}
}

int AKillThemAllGameMode::GetWaveNumber() const
{
	return Wave;
}



void AKillThemAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld())) {

		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;

		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);

	}
}

