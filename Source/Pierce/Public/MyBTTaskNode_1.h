// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTTaskNode_1.generated.h"

/**
 * 
 */
UCLASS()
class PIERCE_API UMyBTTaskNode_1 : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	void UBTTask_ExecutarFuncao();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
