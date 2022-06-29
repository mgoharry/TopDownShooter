// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyCharacter.h"

void AEnemyAIController::BeginPlay() {

	Super::BeginPlay();


	if (AIBehavior == nullptr) return;

	RunBehaviorTree(AIBehavior);
	//GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());

	

}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AEnemyAIController::IsDead() const
{
	AEnemyCharacter* ControlledCharacter = Cast<AEnemyCharacter>(GetPawn());

	if (ControlledCharacter != nullptr) {
		return ControlledCharacter->isDead();
	}

	return true;
}
