// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BotPersonagem.generated.h"

UCLASS()
class PIERCE_API ABotPersonagem : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABotPersonagem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Arma")
	TSubclassOf<class AArma> BP_Arma;

	UPROPERTY(EditAnywhere, Category = "Health")
	float Health;

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	bool bEstaMorto;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	class AArma* ArmaInimigo;

	UFUNCTION()
	void SetHealth(float Dano);

	UFUNCTION()
	float GetHealth();

	UFUNCTION()
	bool IsEstaMorto();
};
