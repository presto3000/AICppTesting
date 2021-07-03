// Fill out your copyright notice in the Description page of Project Settings.


#include "IsPlayerInRange.h"
#include "NPC_AIController.h"
#include "NPC.h"
#include "Runtime/Engine//Classes/Kismet/GameplayStatics.h"
#include  "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "blackboard_keys.h"

UIsPlayerInRange::UIsPlayerInRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT ("Is Player in Melee Range ");
}

void UIsPlayerInRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	// get NPC

	if(ANPC_AIController* const cont = Cast<ANPC_AIController>(OwnerComp.GetAIOwner()))
	{
		if(ANPC* const NPC = Cast<ANPC>(cont->GetPawn()))
		{

	//get player character
	if(ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{

				float const Distance = NPC->GetDistanceTo(player);

				UE_LOG(LogTemp, Warning, TEXT("Distance: %d"), Distance);

				//write true or false depending on whether the player is within melee_range
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), NPC->GetDistanceTo(player)<=melee_range);
			}	
		}
	}
	
}
