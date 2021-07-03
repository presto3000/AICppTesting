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

	ANPC_AIController* const cont = Cast<ANPC_AIController>(OwnerComp.GetAIOwner());
	ANPC* const npc = Cast<ANPC>(cont->GetPawn());

	//get player character
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	//write true or false depending on whether the player is within melee_range
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), npc->GetDistanceTo(player)<=melee_range);
	
	
	
}
