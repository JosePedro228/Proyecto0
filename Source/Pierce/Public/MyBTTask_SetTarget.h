// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTTask_SetTarget.generated.h"

UCLASS()
class PIERCE_API UMyBTTask_SetTarget : public UBTTaskNode
{
    GENERATED_BODY()

public:
    UMyBTTask_SetTarget();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
    /** Aqui você marca como EditAnywhere e expõe para o editor */
    UPROPERTY(EditAnywhere, Category = "Blackboard")
    FBlackboardKeySelector TargetKey;
};

