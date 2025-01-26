// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPuppet.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerTPS.h"
#include "AIController.h"       
#include "GameFramework/Actor.h" 
#include "GameFramework/Character.h" 
#include "AIController.h"       
#include "GameFramework/PlayerController.h" 
#include "Engine/World.h"                   
#include "DrawDebugHelpers.h"               
#include "CollisionQueryParams.h"          
#include "Engine/EngineTypes.h"             
#include "AIController.h"                   




// Sets default values
AMyPuppet::AMyPuppet()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FPlayerTPS = Cast<APlayerTPS>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerTPS::StaticClass()));
}

// Called when the game starts or when spawned
void AMyPuppet::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void AMyPuppet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AMyPuppet::MoveToClickLocation()
{
	FVector TargetLocation = FPlayerTPS->HitResu().Location;

	// Manter o Z atual do personagem
	TargetLocation.Z = GetActorLocation().Z;

	//UE_LOG(LogTemp, Warning, TEXT("Fui Acionado"));
	AAIController* AIController = Cast<AAIController>(GetController());
	UE_LOG(LogTemp, Warning, TEXT("Mov Puppet: X=%f, Y=%f, Z=%f"), TargetLocation.X, TargetLocation.Y, TargetLocation.Z);
	if (AIController)
	{
		AIController->MoveToLocation(TargetLocation);
	}
}


// Called to bind functionality to input
void AMyPuppet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//PlayerInputComponent->BindAction("AndarPuppet", EInputEvent::IE_Pressed, this, &AMyPuppet::MoveToClickLocation);
}

