#include "MyBTTask_SetTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Character.h"

UMyBTTask_SetTarget::UMyBTTask_SetTarget()
{
    NodeName = "Set Player as Target";
}

EBTNodeResult::Type UMyBTTask_SetTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!PlayerPawn) return EBTNodeResult::Failed;

    OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetKey.SelectedKeyName, PlayerPawn);
    return EBTNodeResult::Succeeded;
}
