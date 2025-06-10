// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTaskNode_1.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BotPersonagem.h"

void UMyBTTaskNode_1::UBTTask_ExecutarFuncao()
{
}

EBTNodeResult::Type UMyBTTaskNode_1::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	ABotPersonagem* NPC = Cast<ABotPersonagem>(AIController->GetPawn());
	if (!NPC) return EBTNodeResult::Failed;

	NPC->ConjurarAtaque();
	return EBTNodeResult::Succeeded;

}
