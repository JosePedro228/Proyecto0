// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTPS.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "WorldCollision.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/TargetPoint.h"
#include "Arma.h"
#include "MyPuppet.h"
#include "Blueprint/UserWidget.h" 
#include "WBP_PlayerHealth.h"
#include "Engine/TimerHandle.h"

// Sets default values
APlayerTPS::APlayerTPS()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmCamera = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArm"));
	SpringArmCamera->TargetArmLength = 300.f;
	SpringArmCamera->AddRelativeLocation(FVector(0.f, 40.f, 50.f));
	SpringArmCamera->bEnableCameraLag = true;
	SpringArmCamera->CameraLagSpeed = 40.f;
	SpringArmCamera->SetupAttachment(RootComponent);

	SpringArmCamera->bUsePawnControlRotation = false;
	SpringArmCamera->bInheritPitch = false;
	SpringArmCamera->bInheritYaw = false;
	SpringArmCamera->bInheritRoll = false;

	CameraPersonagem = CreateDefaultSubobject<UCameraComponent>(FName("CameraPersonagem"));
	CameraPersonagem->SetupAttachment(SpringArmCamera);

	CharacterMesh = GetMesh();
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	Movimentacao = CreateDefaultSubobject<ATargetPoint>(FName("Direita"));
	Movimentacao->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

	RotacaoInicialD = Movimentacao->GetActorRotation();
}
// Called when the game starts or when spawned
void APlayerTPS::BeginPlay()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	Super::BeginPlay();
	PlayerController->bShowMouseCursor = true;
	PlayerController->bEnableClickEvents = false;
	PlayerController->bEnableMouseOverEvents = false;


	Super::BeginPlay();
	FActorSpawnParameters Parametros;
	Parametros.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ArmaPlayer = GetWorld()->SpawnActor<AArma>(BP_Arma, FTransform(), Parametros);
	ArmaPlayer->AttachToComponent(Cast<USceneComponent>(GetMesh()), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("SocketDaArma"));

	// Obtém a localização atual do jogador
	FVector PlayerLocation = GetActorLocation();


	FVector SpawnOffset = FVector(20.f, 0.f, 0.f);


	FVector SpawnLocation = PlayerLocation + SpawnOffset;


	FRotator SpawnRotation = GetActorRotation();


	FTransform SpawnTransform(SpawnRotation, SpawnLocation);

	PuppetPlayer = GetWorld()->SpawnActor<AMyPuppet>(BP_MyPuppet, SpawnTransform);
	
	bEstaMorto = false;

	if (HealthWidgetClass) // UPROPERTY com TSubclassOf<UUserWidget>
	{
		HealthWidget = CreateWidget<UUserWidget>(GetWorld(), HealthWidgetClass);
		if (HealthWidget)
		{
			HealthWidget->AddToViewport();
		}
	}

	auto* HealthBar = Cast<UWBP_PlayerHealth>(HealthWidget);
	if (HealthBar)
	{
		HealthBar->SetHealthPercent(Vida / 100.f);
	}
}
void APlayerTPS::MoverParaFrente(float Valor)
{
	AddMovementInput(Movimentacao->GetActorForwardVector() * Valor);
}

void APlayerTPS::MoverDireita(float Valor)
{
	AddMovementInput(Movimentacao->GetActorRightVector() * Valor);
}

void APlayerTPS::Atirar()
{
	ArmaPlayer->Fire();
}

void APlayerTPS::AndarPuppet()
{
	PuppetPlayer->MoveToClickLocation();
}

void APlayerTPS::AtacarPuppet()
{
	PuppetPlayer->ConjurarAtaque();
}

FHitResult APlayerTPS::HitResu()
{
	FHitResult hitResult;
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, hitResult);
	return hitResult;
}

void APlayerTPS::SetVida(float Dano)
{
	Vida = Vida - Dano;
	if (Vida <= 0)
	{
		bEstaMorto = true;
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController)
		{
			DisableInput(PlayerController);
		}
		CarregarLoseMenu();
		UE_LOG(LogTemp, Warning, TEXT("Player Morto"));
	}
	auto* HealthBar = Cast<UWBP_PlayerHealth>(HealthWidget);
	if (HealthBar)
	{
		HealthBar->SetHealthPercent(Vida / 100.f);
	}

}

void APlayerTPS::CarregarLoseMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("LoseMenu"));
}

// Called every frame
void APlayerTPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Movimentacao->SetActorRotation(RotacaoInicialD);
	GetMouseLocation();
}
void APlayerTPS::GetMouseLocation()
{
	//note that the line 58-59 is seen pretty common on the internet to find the cursor porjection
	//onto the internet, however, they do not give me the right vector.
	//FVector CursorWorldLocation, CursorWorldDirection;
	//GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(CursorWorldLocation, CursorWorldDirection);
	//=====================================================================//

	//gets location of the actor in the world
	FVector CurrLoc = this->GetActorLocation();

	// the right method of getting cursor location!!! note: i used the exact same method in the Epic Top Down Blueprint.

	FVector hitLoc = HitResu().Location;

	//geting the original rotation of the acter;
	FRotator newRot = this->GetActorRotation();
	//Using atan2 function to get the degree between our character location and cursor location
	// aka how much we want the character to rotate
	float newYaw = (hitLoc - CurrLoc).Rotation().Yaw;;
	//Using that degree as the Yaw(rotating around Z axis) of our Frotator
	newRot.Yaw = newYaw;

	FName HitBoneName = HitResu().BoneName;


	
	//UE_LOG(LogTemp, Warning, TEXT("Player Location: X=%f, Y=%f, Z=%f"), this->GetActorLocation().X, this->GetActorLocation().Y, this->GetActorLocation().Z);

	//UE_LOG(LogTemp, Warning, TEXT("Mouse Location: X=%f, Y=%f, Z=%f"), hitLoc.X, hitLoc.Y, hitLoc.Z);
	
	//in the end, we set it;
	if (hitLoc.X<= this->GetActorLocation().X -25 || hitLoc.X >= this->GetActorLocation().X + 25 && hitLoc.Y <= this->GetActorLocation().Y - 25 || hitLoc.Y >= this->GetActorLocation().Y + 25 &&!bEstaMorto)
	{

	this->GetController()->SetControlRotation(newRot);
	}
}
// Called to bind functionality to input
void APlayerTPS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoverParaFrente", this, &APlayerTPS::MoverParaFrente);
	PlayerInputComponent->BindAxis("MoverDireita", this, &APlayerTPS::MoverDireita);
	PlayerInputComponent->BindAction("Atirar", EInputEvent::IE_Pressed, this, &APlayerTPS::Atirar);
	PlayerInputComponent->BindAction("AndarPuppet", EInputEvent::IE_Pressed, this, &APlayerTPS::AndarPuppet);
	PlayerInputComponent->BindAction("AtacarPuppet", EInputEvent::IE_Pressed, this, &APlayerTPS::AtacarPuppet);
}


