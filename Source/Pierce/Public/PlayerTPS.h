// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerTPS.generated.h"

UCLASS()
class PIERCE_API APlayerTPS : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerTPS();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoverParaFrente(float Valor);

	void MoverDireita(float Valor);

	void Atirar();

	void AndarPuppet();

	void AtacarPuppet();

	float Vida= 100.f;

	FTimerHandle TimerHandle3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* CameraPersonagem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CameraBoom")
	class USpringArmComponent* SpringArmCamera;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USkeletalMeshComponent* CharacterMesh;

	UPROPERTY(EditAnywhere, Category = "Target")
	class ATargetPoint* Movimentacao; 

	UPROPERTY(EditAnywhere, Category = "Arma")
	TSubclassOf<class AArma> BP_Arma;

	UPROPERTY(EditAnywhere, Category = "Puppet")
	TSubclassOf<class AMyPuppet> BP_MyPuppet;

	FRotator RotacaoInicialD;

	UFUNCTION()
	void CarregarLoseMenu();


public:		
	class AMyPuppet* PuppetPlayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class AArma* ArmaPlayer;
	UFUNCTION()
	FHitResult HitResu();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bEstaMorto;

	void SetVida(float Dano);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> HealthWidgetClass;

	UUserWidget* HealthWidget;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GetMouseLocation();
};
