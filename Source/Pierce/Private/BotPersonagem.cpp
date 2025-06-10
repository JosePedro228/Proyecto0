// Fill out your copyright notice in the Description page of Project Settings.


#include "BotPersonagem.h"
#include "Engine/World.h"
#include "PlayerTPS.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"  
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "AIController.h"  
#include "MyGameMode.h"
#include "Components/CapsuleComponent.h" // Asegúrate de incluir este encabezado para UCapsuleComponen
#include "Sound/SoundBase.h"

// Sets default values
ABotPersonagem::ABotPersonagem()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Health = 100.f;
}

// Called when the game starts or when spawned
void ABotPersonagem::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters Parametros;
	Parametros.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


    bPodeAtacar = true;

    bEstaMorto = false;

    GameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void ABotPersonagem::VelocidadeDeAtaque()
{
    bPodeAtacar = true;
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
        bEstaMorto = true;
		//UE_LOG(LogTemp, Warning, TEXT("Eu estou morto"));
	}
    if (bEstaMorto && bEuContinuomMorto)
    {
		bEuContinuomMorto = false;
        AAIController* AIController = Cast<AAIController>(GetController());
        if (AIController)
        {
            AIController->UnPossess(); // Remove o controle do bot
        }
        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        if (GameMode)
        {
            GameMode->InimigosDisponivesParaSpawn++;
           // UE_LOG(LogTemp, Warning, TEXT(" InimigosDisponivesParaSpawn = %d"), GameMode->InimigosDisponivesParaSpawn);
        }
        GetWorld()->GetTimerManager().SetTimer(TimerHandle1, this,&ABotPersonagem::AutoDestroir, 2.16f, false);

    }

}

void ABotPersonagem::HitBesta()
{
    if (bHitEspada)
    {
		SetHealth(75.f);
    }
    else
    {

		SetHealth(25.f);
		bHitBesta = true;

        // Impede ataque
        bPodeAtacar = false;

        // Desabilita movimento
        GetCharacterMovement()->DisableMovement();

        // Define um timer para restaurar o estado normal
        GetWorld()->GetTimerManager().SetTimer(
            TimerHandle2, this, &ABotPersonagem::Desparalisar, 0.5f, false);
    }
}

void ABotPersonagem::HitEspada()
{
    if (bHitBesta)
    {
        SetHealth(75.f);
    }
    else
    {
        SetHealth(25.f);
        bHitEspada = true;
        // Impede ataque
        bPodeAtacar = false;
        // Desabilita movimento
        GetCharacterMovement()->DisableMovement();
        // Define um timer para restaurar o estado normal
        GetWorld()->GetTimerManager().SetTimer(
            TimerHandle3, this, &ABotPersonagem::Desparalisar, 0.5f, false);
	}
}

void ABotPersonagem::Desparalisar()
{
    bHitBesta = false;
    bHitEspada = false;
    // Restaura o movimento
    GetCharacterMovement()->SetMovementMode(MOVE_Walking);
    // Permite ataque novamente
	bPodeAtacar = true;
}

void ABotPersonagem::AutoDestroir()

{
    this->Destroy();

}

void ABotPersonagem::ConjurarAtaque()
{
   
    if (bPodeAtacar) {
        bPodeAtacar = false;
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABotPersonagem::AttackMelee, 1.5f, false);
    }

}

void ABotPersonagem::AttackMelee()
{

        bool bAcertou = true;
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
        UGameplayStatics::PlaySoundAtLocation(this, SAtaqueZombie, this->GetActorLocation());
        if (bHit)
        {
            for (FHitResult Hit : HitResults)
            {
                AActor* HitActor = Hit.GetActor();
               // UE_LOG(LogTemp, Warning, TEXT("Atingiu: %s"), *HitActor->GetName());

  
                if (HitActor && HitActor->ActorHasTag("Player") && bAcertou)
                {
                    APlayerTPS* Alvo = Cast<APlayerTPS>(HitActor);

                    Alvo->SetVida(25.f);
                    // Aplicar dano ao alvo atingido
                    //HitActor->Destroy();
                    //UE_LOG(LogTemp, Warning, TEXT("Acertei un inigo"));
                    bAcertou = false;
                }
            }
            bAcertou = true;
        }
        bPodeAtacar = true;
 
}




