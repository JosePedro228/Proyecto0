#include "MyGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "BotPersonagem.h" // Inclua o cabeçalho do seu bot personagem
#include "PlayerTPS.h" // Inclua o cabeçalho do seu player
#include "Sound/SoundBase.h"


// Fix for the SetTimer issue by using a valid FTimerHandle instance.  
void AMyGameMode::BeginPlay()  
{  
    Super::BeginPlay();  



	Player = Cast<APlayerTPS>(UGameplayStatics::GetPlayerPawn(this, 0)); // Obter referência ao PlayerPawn
    // Coletar todos os TargetPoints na cena  
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), SpawnPoints);  

    SpawnEnemy();
    // Iniciar timer para spawn periódico  
    if (BotPersonagem && SpawnPoints.Num() > 0)
    {  
        GetWorldTimerManager().SetTimer(
            SpawnEnemyTimerHandle, this, &AMyGameMode::SpawnEnemy, SpawnInterval, true);
    }  
    if (MusicaAmbiente)
    {
        UGameplayStatics::PlaySound2D(GetWorld(), MusicaAmbiente, 1.0f, 1.0f, 0.0f);
    }
}
/*
void AMyGameMode::SpawnEnemy()
{
	if (BotPersonagem && SpawnPoints.Num() > 0 && Player)
	{
		FVector LocalizacaoPlayer = Player->GetActorLocation(); // Use Player's location if needed
		TArray <AActor*> SpanwPointValidos;
		SpanwPointValidos.SetNum(InimigosDisponivesParaSpawn);
		int32 j = 0;
        for (int32 i = 0; i < SpawnPoints.Num(); ++i)
        {
            AActor* SpawnPoint = SpawnPoints[i];
            if (SpawnPoint)
            {
				j = 0; 
				FVector LocalizacaoSpawnPoint = SpawnPoint->GetActorLocation();

                bool bInserido = false;
                for (j = 0; j < SpanwPointValidos.Num(); ++j)
                {
                    if (SpanwPointValidos[j] != nullptr)
                    {
                        FVector LocalizacaoExistente = SpanwPointValidos[j]->GetActorLocation();
                        if (FVector::Dist(LocalizacaoSpawnPoint, LocalizacaoPlayer) < FVector::Dist(LocalizacaoExistente, LocalizacaoPlayer))
                        {
                            SpanwPointValidos.Insert(SpawnPoint, j);
                            bInserido = true;
                            break;
                        }
                    }
                }
                if (!bInserido)
                {
                    SpanwPointValidos.Add(SpawnPoint);
                }
            }
        }
        SpanwPointValidos.SetNum(InimigosDisponivesParaSpawn);
        while (InimigosDisponivesParaSpawn>0)
        {

      
            
            for (int32 i = 0; i < SpanwPointValidos.Num(); ++i)
            {
                if (SpanwPointValidos[i] != nullptr)
                {
                    FVector SpawnLocation = SpanwPointValidos[i]->GetActorLocation();
                    FRotator SpawnRotation = SpanwPointValidos[i]->GetActorRotation();
                    GetWorld()->SpawnActor<ABotPersonagem>(BotPersonagem, SpawnLocation, SpawnRotation);
                    InimigosDisponivesParaSpawn--;
                    if (InimigosDisponivesParaSpawn == 0)
                    {
                        break;
                    }
                }
            }
            
		}
	}
}
*/
void AMyGameMode::SpawnEnemy()
{
    //UE_LOG(LogTemp, Warning, TEXT("SpawnEnemy executado! InimigosDisponivesParaSpawn = %d"), InimigosDisponivesParaSpawn);

    if (BotPersonagem && SpawnPoints.Num() > 0 && Player)
    {
        FVector LocalizacaoPlayer = Player->GetActorLocation();

        // Copiar os spawn points válidos
        TArray<AActor*> SpawnPointsValidos;
        for (AActor* SpawnPoint : SpawnPoints)
        {
            if (SpawnPoint)
            {
                SpawnPointsValidos.Add(SpawnPoint);
            }
        }

        // Ordenar por proximidade ao player
        SpawnPointsValidos.Sort([&](const AActor& A, const AActor& B)
            {
                return FVector::Dist(A.GetActorLocation(), LocalizacaoPlayer) < FVector::Dist(B.GetActorLocation(), LocalizacaoPlayer);
            });

        // Garantir que não vai ultrapassar a quantidade permitida
        int32 QuantidadeParaSpawnar = FMath::Min(InimigosDisponivesParaSpawn, SpawnPointsValidos.Num());

        for (int32 i = 0; i < QuantidadeParaSpawnar; ++i)
        {
            FVector SpawnLocation = SpawnPointsValidos[i]->GetActorLocation();
            FRotator SpawnRotation = SpawnPointsValidos[i]->GetActorRotation();

            GetWorld()->SpawnActor<ABotPersonagem>(BotPersonagem, SpawnLocation, SpawnRotation);
            InimigosDisponivesParaSpawn--;
        }
    }
}