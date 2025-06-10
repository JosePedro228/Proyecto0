// Fill out your copyright notice in the Description page of Project Settings.


#include "Arma.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Estacas.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/SkeletalMesh.h"
#include "Components/ArrowComponent.h"
#include "PlayerTPS.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundBase.h"
#include "TimerManager.h"
// Sets default values
AArma::AArma()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    MuzzleOffset = FVector(100.0f, 0.0f, 0.0f);
	MeshDaArma = CreateDefaultSubobject<USkeletalMeshComponent>(FName("MalhaDaArma"));
	RootComponent = MeshDaArma;

    SDisparo = nullptr;

	ConstructorHelpers::FObjectFinder<USkeletalMesh>MalhaDaArma(TEXT("/Script/Engine.SkeletalMesh'/Game/Mesh/Weapons/Besta/Crossbow.Crossbow'"));

	if (MalhaDaArma.Succeeded())
	{
		MeshDaArma->SetSkeletalMesh(MalhaDaArma.Object);
	}
	SetaDaArma = CreateDefaultSubobject<UArrowComponent>(FName("SetaCanoDaArma"));
	//Aqui solicitamos que este construtor seja anexado, atrelado, aclopado a malhada da arma
//Contudo é solicitado um attach para algo que ainda não foi configurado pois primeiro a classe c++ é executada e depois qualquer blueprint que tem esta classe como pai
//Assim o mesh ou skeletalmesh da arma ainda não estará disponível aqui pois está sendo setado na bleprint.
//Logo precisamos configurar no código a malhadadaarma!
//Outra coisa importante e recomendada pela unreal engine é que no construtor
//use a função SEtupAttachment para fazer o attach de algum componente a seu dono
//logo somente usar attachtocomponent fora do construtor
	SetaDaArma->SetupAttachment(MeshDaArma, FName("MuzzleFlashSocket"));
	SetaDaArma->SetRelativeLocation(FVector(1.5f, 0.f, -1.2));
	SetaDaArma->SetRelativeScale3D(FVector(0.3f, 0.8f, 0.7f));

    FPlayerTPS = Cast<APlayerTPS>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerTPS::StaticClass()));
}

void AArma::Fire()
{
    SetaDaArma = FindComponentByClass<UArrowComponent>();

    if (SetaDaArma && bPodeAtirar)
    {
        if (FPlayerTPS)
        {


            if (BP_Estacas)
            {
                FVector MuzzleLocation = SetaDaArma->GetComponentLocation() ;
                FRotator MuzzleRotation = SetaDaArma->GetComponentRotation();
                UWorld* World = GetWorld();
                if (SDisparo)
                {
                    UGameplayStatics::PlaySoundAtLocation(SetaDaArma, SDisparo, MuzzleLocation);
                }
                if (World)
                {
                    FActorSpawnParameters SpawnParams;
                    SpawnParams.Owner = this;
                    SpawnParams.Instigator = GetInstigator();

                    // Spawn the projectile at the muzzle
                    AEstacas* Projectile = World->SpawnActor<AEstacas>(BP_Estacas, MuzzleLocation, MuzzleRotation, SpawnParams);
                    if (Projectile)
                    {
                        // Set the projectile's initial trajectory
                        FVector LaunchDirection = (FPlayerTPS->HitResu().Location - MuzzleLocation).GetSafeNormal2D();
                        Projectile->FireInDirection(LaunchDirection);

                        USphereComponent* HitBox = Projectile->FindComponentByClass<USphereComponent>();

                        if (HitBox !=nullptr)
                        {
                            UE_LOG(LogTemp, Warning, TEXT("Found MeshComponent in ActorA!"));
                            HitBox->IgnoreActorWhenMoving(this, true);

                                // Ignorar avô (pai do ator que dispara o projétil)
                                AActor* GrandparentActor = GetAttachParentActor();
                                if (GrandparentActor)
                                {
                                    HitBox->IgnoreActorWhenMoving(GrandparentActor, true);
                                }
                        }
                    }
                }
            }
        }
        bPodeAtirar = false;
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AArma::FireRate, 0.28f, false);

    }

    
}

// Called when the game starts or when spawned
void AArma::BeginPlay()
{
	Super::BeginPlay();
    bPodeAtirar = true;
}

// Called every frame
void AArma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AArma::FireRate()
{
    bPodeAtirar = true;
}


