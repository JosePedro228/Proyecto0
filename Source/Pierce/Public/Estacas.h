// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Estacas.generated.h"

UCLASS()
class PIERCE_API AEstacas : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEstacas();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

	// Função que será chamada ao detectar sobreposição


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void FireInDirection(const FVector& ShootDirection);

private:
	UPROPERTY(EditAnywhere, Category = "Esfera")
	class USphereComponent* HitBox;

	UPROPERTY(EditAnywhere, Category = "Particula")
	class UParticleSystemComponent* Particula;

	UPROPERTY(EditAnywhere, Category = "Luz")
	class UPointLightComponent* Luz;

	// Components
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* ProjectileMeshComponent;

	// Function to handle the hit event
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
