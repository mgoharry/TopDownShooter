// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_ClearBBValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTTask_ClearBBValue::UMyBTTask_ClearBBValue() {

	NodeName = TEXT("Clear Blackboard Value");
}

EBTNodeResult::Type UMyBTTask_ClearBBValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	
	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	return EBTNodeResult::Succeeded;

}
