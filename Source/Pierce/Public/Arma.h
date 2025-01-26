// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arma.generated.h"

UCLASS()
class PIERCE_API AArma : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArma();

	UPROPERTY(EditAnywhere, Category = "Mesh da Arma")
	class USkeletalMeshComponent* MeshDaArma;

	UPROPERTY(EditAnywhere, Category = "Seta da Arma")
	class UArrowComponent* SetaDaArma;

	UFUNCTION()
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	private:
	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<class AEstacas> BP_Estacas;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<class APlayerTPS> PlayerTPS;

	APlayerTPS* FPlayerTPS;

    UPROPERTY(EditAnywhere, Category = "Combat")
    FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, Category="Audio")
	class USoundBase* SDisparo;

	FTimerHandle TimerHandle;

	bool bPodeAtirar;

	void FireRate();
};
