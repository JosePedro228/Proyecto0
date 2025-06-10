// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
class AMyGameMode; // Forward declaration to avoid circular dependency
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

	UPROPERTY(EditAnywhere, Category = "Health")
	float Health;

	AMyGameMode* GameMode;

	FTimerHandle TimerHandle;

	FTimerHandle TimerHandle1;

	FTimerHandle TimerHandle2;

	FTimerHandle TimerHandle3;

	void AutoDestroir();

	void VelocidadeDeAtaque();

	void Desparalisar();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEstaMorto;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPodeAtacar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHitEspada;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHitBesta;

	UFUNCTION()
	void AttackMelee();

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackRange = 2.0f; // Alcance do ataque corpo a corpo

	UFUNCTION()
	void SetHealth(float Dano);

	UFUNCTION()
	void ConjurarAtaque();

	UFUNCTION()
	void HitBesta();

	UFUNCTION()
	void HitEspada();

	bool bEuContinuomMorto = true;

	UPROPERTY(EditAnywhere, Category = "Audio")
	class USoundBase* SAtaqueZombie;

	int32 Valor;
};
