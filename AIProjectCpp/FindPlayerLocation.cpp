// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPlayerLocation.h"

#include "blackboard_keys.h"
#include "NavigationSystem.h"
#include "NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UFindPlayerLocation::UFindPlayerLocation(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	//get player character and the NPC's controller
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0 );
	auto const cont = Cast<ANPC_AIController>(owner_comp.GetAIOwner());

	//get player location to use as an origin
	FVector const player_location = player ->GetActorLocation();
	if(search_random)
	{
		FNavLocation loc;
		//get the navigation system and generate a random location near the player
		UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent((GetWorld()));
		if(nav_sys->GetRandomPointInNavigableRadius(player_location, search_radius, loc, nullptr))
		{
			owner_comp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), loc.Location);
			
		}
	}
	else
	{
		owner_comp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), player_location);
	}

	//finish with success
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	
	return EBTNodeResult::Succeeded;
}
