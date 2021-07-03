// Fill out your copyright notice in the Description page of Project Settings.


#include "IncrementPathIndex.h"

#include "NPC.h"
#include "NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "blackboard_keys.h"
#include "cmath"

UIncrementPathIndex::UIncrementPathIndex(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Increment Path Index");
}

EBTNodeResult::Type UIncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get the AI controller
	if(ANPC_AIController* const controller = Cast<ANPC_AIController>(OwnerComp.GetAIOwner()))
	{
		if(ANPC* const npc = Cast<ANPC>(controller->GetPawn()))
		{
		int const no_of_points = npc->get_patrol_path()->num();
		int const min_index = 0;
		int const max_index = no_of_points - 1;
		//get and set the black board index key
		int index = OwnerComp.GetBlackboardComponent()->GetValueAsInt(GetSelectedBlackboardKey());
			if(bidirectional)
			{
				if(index >= max_index && Direction == EDirectionType::Forward)
				{
					Direction = EDirectionType::Reverse;
				}
				else if (index == min_index && Direction == EDirectionType::Reverse)
				{
					Direction = EDirectionType::Forward;
				}		
		}
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(GetSelectedBlackboardKey(),
			(Direction == EDirectionType::Forward ? std::abs(++index) : std::abs(--index)) % no_of_points);

		//Finish with success
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return  EBTNodeResult::Succeeded;
		}
	}
		return  EBTNodeResult::Failed;
}
