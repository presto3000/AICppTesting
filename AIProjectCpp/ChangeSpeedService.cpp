// Fill out your copyright notice in the Description page of Project Settings.

#include "ChangeSpeedService.h"
#include "AIController.h"
#include "NPC.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework//CharacterMovementComponent.h"
UChangeSpeedService::UChangeSpeedService()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Change Speed");
}

void UChangeSpeedService::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	
	if(auto const cont = OwnerComp.GetAIOwner())
	{
		if (ANPC* const npc = Cast<ANPC>(cont->GetPawn()))
		{
		npc->GetCharacterMovement()->MaxWalkSpeed = speed;
		}
	}
}

FString UChangeSpeedService::GetStaticServiceDescription() const
{
	return  FString("Change the NPCs speed");
}
