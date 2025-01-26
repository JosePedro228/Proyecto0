// Fill out your copyright notice in the Description page of Project Settings.


#include "BotPersonagem.h"
#include "Engine/World.h"
#include "Arma.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABotPersonagem::ABotPersonagem()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Health = 0.f;
}

// Called when the game starts or when spawned
void ABotPersonagem::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters Parametros;
	Parametros.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ArmaInimigo = GetWorld()->SpawnActor<AArma>(BP_Arma, FTransform(), Parametros);
	ArmaInimigo ->AttachToComponent(Cast<USceneComponent>(GetMesh()), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("SocketDaArma"));
}

// Called every frame
void ABotPersonagem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABotPersonagem::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABotPersonagem::SetHealth(float Dano)
{
	Health = Health - Dano;
	if (Health<= 0)
	{
		IsEstaMorto();
		UE_LOG(LogTemp, Warning, TEXT("Eu estou morto"));
	}
}

float ABotPersonagem::GetHealth()
{
	return 0.0f;
}

bool ABotPersonagem::IsEstaMorto()
{
	return true;
}

