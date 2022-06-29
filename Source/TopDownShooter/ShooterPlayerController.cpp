// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"



void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUDWidget = CreateWidget(this, HUD);
	if (HUDWidget != nullptr) {
		HUDWidget->AddToViewport();
	}
}

void AShooterPlayerController::GameHasEnded(class AActor *EndGameFocus, bool bIsWinner) {

	Super::GameHasEnded(EndGameFocus, bIsWinner);

	HUDWidget->RemoveFromViewport();

	
	if (bIsWinner) {
		
		bShowMouseCursor = true;
		UUserWidget* WinScreenWidget = CreateWidget(this, WinScreen);
		if (WinScreenWidget != nullptr) {
			WinScreenWidget->AddToViewport();
			GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
		}
	}
	else {
		bShowMouseCursor = true;
		UUserWidget* LoseScreenWidget = CreateWidget(this, LoseScreen);
		if (LoseScreenWidget != nullptr) {
			LoseScreenWidget->AddToViewport();
		}
	}

	
}