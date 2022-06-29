// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	virtual void GameHasEnded(class AActor *EndGameFocus = nullptr, bool bIsWinner = false) override;

private:

	UPROPERTY(EditAnywhere)
		float RestartDelay = 7.f;

	FTimerHandle RestartTimer;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> LoseScreen;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> WinScreen;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> HUD;
	UPROPERTY()
	UUserWidget* HUDWidget;
};
