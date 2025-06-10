// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPuppet.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerTPS.h"
#include "AIController.h"       
#include "GameFramework/Actor.h" 
#include "GameFramework/Character.h"       
#include "GameFramework/PlayerController.h" 
#include "Engine/World.h"                   
#include "DrawDebugHelpers.h"               
#include "CollisionQueryParams.h"          
#include "Engine/EngineTypes.h"             
#include "TimerManager.h"
#include "BotPersonagem.h"
#include "Sound/SoundBase.h"







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

    bPodeAtacar = true;
	
}

void AMyPuppet::ConjurarAtaque()
{
    AAIController* AIController = Cast<AAIController>(GetController());
    if (bPodeAtacar && AIController)
    {
        AIController->StopMovement();
        bPodeAtacar = false;
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMyPuppet::AttackMelee, 0.5f, false);
    }
}


// Called every frame
void AMyPuppet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AMyPuppet::MoveToClickLocation()
{
    if (bPodeAtacar)
    {
	    FVector TargetLocation = FPlayerTPS->HitResu().Location;

	    // Manter o Z atual do personagem
	    TargetLocation.Z = GetActorLocation().Z;

	    //UE_LOG(LogTemp, Warning, TEXT("Fui Acionado"));
	    AAIController* AIController = Cast<AAIController>(GetController());
	    //UE_LOG(LogTemp, Warning, TEXT("Mov Puppet: X=%f, Y=%f, Z=%f"), TargetLocation.X, TargetLocation.Y, TargetLocation.Z);
	    if (AIController)
	    {
		    AIController->MoveToLocation(TargetLocation);
	    }
    }
}

void AMyPuppet::AttackMelee()
{
    FVector StartLocation = GetActorLocation();
    FVector ForwardVector = GetActorForwardVector();
    FVector EndLocation = StartLocation + (ForwardVector * AttackRange);

    TArray<AActor*> IgnoredActors;
    IgnoredActors.Add(this);

    // Variáveis para armazenar os resultados do traço de ataque
    TArray<FHitResult> HitResults;

    // Faz um traço esférico para detectar inimigos dentro da área de ataque
    bool bHit = UKismetSystemLibrary::SphereTraceMulti(
        this,
        StartLocation,
        EndLocation,
        100.0f, // Raio do traço
        UEngineTypes::ConvertToTraceType(ECC_Pawn),
        false,
        IgnoredActors,
        EDrawDebugTrace::None, // Mostra o traço para debug
        HitResults,
        true
    );
    UGameplayStatics::PlaySoundAtLocation(this, SAtaquePuppet, this->GetActorLocation());
    if (bHit)
    {
        for (FHitResult Hit : HitResults)
        {
            AActor* HitActor = Hit.GetActor();
            //UE_LOG(LogTemp, Warning, TEXT("Atingiu: %s"), *HitActor->GetName());
            if (HitActor)
            {


                ABotPersonagem* Alvo = Cast<ABotPersonagem>(HitActor);
                if (HitActor && HitActor->ActorHasTag("Inimigo")&&!Alvo->bHitEspada)
                {
                    // Aplicar dano ao alvo atingido
                    Alvo->HitEspada();
                    //UE_LOG(LogTemp, Warning, TEXT("Acertei un inigo"));
                }
            }
        }
    }

    bPodeAtacar = true;
}


// Called to bind functionality to input
void AMyPuppet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//PlayerInputComponent->BindAction("AndarPuppet", EInputEvent::IE_Pressed, this, &AMyPuppet::MoveToClickLocation);
}

