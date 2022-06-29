// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_EnemyShoot.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "EnemyCharacter.h"


UBTTask_EnemyShoot::UBTTask_EnemyShoot() {

	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_EnemyShoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;

	AEnemyCharacter* Character = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (Character == nullptr) return EBTNodeResult::Failed;

	Character->Shoot();

	return EBTNodeResult::Succeeded;
}
