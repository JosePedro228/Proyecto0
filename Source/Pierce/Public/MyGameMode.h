#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/TargetPoint.h"

class APlayerTPS;
#include "MyGameMode.generated.h"


UCLASS()
class PIERCE_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	APlayerTPS* Player;

	int32 InimigosDisponivesParaSpawn = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* MusicaAmbiente;
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<class ABotPersonagem> BotPersonagem;

	UPROPERTY()
	TArray<AActor*> SpawnPoints;

	UFUNCTION()
	void SpawnEnemy();

	FTimerHandle SpawnEnemyTimerHandle;


	UPROPERTY(EditAnywhere, Category = "Spawning")
	float SpawnInterval = 30.0f; // segundos
};
