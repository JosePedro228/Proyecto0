// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPuppet.generated.h"

UCLASS()
class PIERCE_API AMyPuppet : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPuppet();
	void MoveToClickLocation();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackRange = 2.0f; // Alcance do ataque corpo a corpo

	UPROPERTY(EditAnywhere, Category = "Health")
	float Health;

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	bool bEstaMorto;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* CharacterMesh;

	TSubclassOf<class APlayerTPS> PlayerTPS;

	FTimerHandle TimerHandle;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AttackMelee();

	APlayerTPS* FPlayerTPS;

	UFUNCTION()
	void ConjurarAtaque();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPodeAtacar;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Audio")
	class USoundBase* SAtaquePuppet;

};
