// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TopDownShooterGameModeBase.h"
#include "EnemySpawner.h"
#include "KillThemAllGameMode.generated.h"

/**
 * 

 */
class AEnemyCharacter;
UCLASS()
class TOPDOWNSHOOTER_API AKillThemAllGameMode : public ATopDownShooterGameModeBase
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	virtual void PawnKilled(APawn* PawnKilled) override;

	void SpawnWave(int WaveNumber);

	UFUNCTION(BlueprintPure)
		int GetWaveNumber() const;

private:
	void EndGame(bool bIsPlayerWinner);

protected:
		
	UPROPERTY(EditAnywhere)
		TSubclassOf<AEnemyCharacter> Enemy;
	

	TArray<AActor*> SpawnPoints;
	int Wave = 1;

	

};
