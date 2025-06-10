// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_PlayerHealth.generated.h"

/**
 * 
 */
UCLASS()
class PIERCE_API UWBP_PlayerHealth : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void SetHealthPercent(float Percent);

};
