// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BotIAController.generated.h"

/**
 * 
 */
UCLASS()
class PIERCE_API ABotIAController : public AAIController
{
	GENERATED_BODY()
	
protected: 
	ABotIAController();
	virtual void OnPossess(APawn* InPawn) override;

	//O SensingComponent Encapsula configuraçoes e funcionalidades sensoriais(visao, audiçao) de um ator.

	UPROPERTY(EditDefaultsOnly)
	class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTreeComponent* BehaviorTreeComp;

	UPROPERTY(EditDefaultsOnly)

	class UBlackboardComponent* BlackboardComp;

	UFUNCTION()
	void OnSeePawn(class APawn* SensedPawn);
};
