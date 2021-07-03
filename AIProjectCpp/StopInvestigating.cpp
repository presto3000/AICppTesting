// Fill out your copyright notice in the Description page of Project Settings.


#include "StopInvestigating.h"
#include "NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "blackboard_keys.h"



UStopInvestigating::UStopInvestigating(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Stop Investigating");
}

EBTNodeResult::Type UStopInvestigating::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get the NPC controller and write false to the blackboard key "IsInvestigating"
	auto const cont = Cast <ANPC_AIController>(OwnerComp.GetAIOwner());
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(bb_keys::is_investigating, false);

	//finish with success
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
	
	

	
}
