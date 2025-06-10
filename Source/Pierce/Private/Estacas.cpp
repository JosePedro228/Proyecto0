// Fill out your copyright notice in the Description page of Project Settings.


#include "Estacas.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BotPersonagem.h"

// Sets default values
AEstacas::AEstacas()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HitBox = CreateDefaultSubobject<USphereComponent>(TEXT("HitBox"));
	HitBox->SetCollisionProfileName(TEXT("Projectile"));
	RootComponent = HitBox;

	// Use this component to drive this projectile's movement
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
	ProjectileMovementComponent->InitialSpeed = 2000.f;
	ProjectileMovementComponent->MaxSpeed = 3000.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;


	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ProjectileMeshComponent->SetupAttachment(HitBox);

	Particula = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particula"));
	Particula->SetupAttachment(HitBox);
	
	Luz = CreateDefaultSubobject<UPointLightComponent>(TEXT("Luz"));
	Luz->SetupAttachment(HitBox);

	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	HitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	HitBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	HitBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);


}

// Called when the game starts or when spawned
void AEstacas::BeginPlay()
{
	Super::BeginPlay();
	HitBox->SetEnableGravity(false);
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &AEstacas::OnOverlapBegin);
}

// Called every frame
void AEstacas::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEstacas::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AEstacas::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABotPersonagem* Alvo = Cast<ABotPersonagem>(OtherActor);
	if (OtherActor && OtherActor->ActorHasTag("Inimigo"))
	{
		Alvo->HitBesta();
		Destroy();
	}

	
}

