// Fill out your copyright notice in the Description page of Project Settings.


#include "BotIAController.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "BotPersonagem.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

ABotIAController::ABotIAController() 
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(FName("PawnSensingComp"));
	//Aqui Configuramos como os sensores do inimigo deverão atuar
//Deve fazer a varredura sensorial a cada 1/4 de segundo .25
	PawnSensingComp->SensingInterval = .25f;
	PawnSensingComp->bOnlySensePlayers = true;
	PawnSensingComp->SetPeripheralVisionAngle(180.f);
	PawnSensingComp->SightRadius = 3000.f;

	//Aqui criamos um component de BT para manipular a BT criada
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(FName("BehaviorTreeComp"));
	//Da mesma forma foi criado um component de BlackBoard para podermos
//Colocar variáveis, alterar seu valor, etc no BlackBoard Criado
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(FName("BlackBoardComp"));

}

void ABotIAController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//Se o sensor do inimigo disparar o evento OnSeePawn significa que ele detectou o nosso jogador(que para ele é seu inimigo)
//Neste caso iremos anexar, amarrar, fazer um binding da função para uma função
//criada por nós para esta classe
	PawnSensingComp->OnSeePawn.AddDynamic(this, &ABotIAController::OnSeePawn);

	if (BehaviorTree)
	{
		//Aqui iniciamos o BlackBosard e a BehaivouTree
		BlackboardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		BehaviorTreeComp->StartTree(*BehaviorTree);
		BlackboardComp->SetValueAsBool("DevePerambular", true);
	}
}

void ABotIAController::OnSeePawn(APawn* SensedPawn)
{
	if (BlackboardComp && SensedPawn)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Eu estou te Vendo"));

		//aqui setamos a variável do BlackBoard Inimigo com o valor do objeto
		//SensedPawn: Este objeto é o retornado quando o game está em execução
		//e o sensor do inimigo detecta seu inimigo(no caso o player)
		//Então o objeto player e colocado em Inimigo que é Object no BlackBoard
		BlackboardComp->SetValueAsObject("Inimigo", SensedPawn);
		//Se esta função for chamada significa que o inimigo VIU(see) um jogador (Pawn) e neste caso deve parar de Perambular
//Assim colocamos false no blackboard para que a arvore de comportamento leia
//e Trate este valor.
		BlackboardComp->SetValueAsBool("DevePerambular", false);
	}
}

