// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasePlayer.h"
#include "NPC_AIController.h"
#include "BehaviorTree//BlackboardComponent.h"
#include "Blueprint//AIBlueprintHelperLibrary.h"
#include "blackboard_keys.h"

UChasePlayer::UChasePlayer(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UChasePlayer::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	//get TargetLocation from blackboard via AI controller
	if(ANPC_AIController* const cont = Cast<ANPC_AIController>(owner_comp.GetAIOwner()))
	{
	FVector const player_location = owner_comp.GetBlackboardComponent()->GetValueAsVector(bb_keys::target_location);

	//move to the player's location
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont, player_location);

	//finish with success
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;

}
