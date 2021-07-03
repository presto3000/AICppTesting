 // Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeAttack.h"
//#include "CombatInterface.h"
#include "AIController.h"
#include "NPC_AIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

UMeleeAttack::UMeleeAttack(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Melee Attack");
}

EBTNodeResult::Type UMeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get AI controller and the NPC
	if(AAIController* const cont = OwnerComp.GetAIOwner())
	{
		//if (ICombatInterface* const icombat = Cast<ICombatInterface>(npc))
		if (ANPC* const npc = Cast<ANPC>(cont->GetPawn()))
			{
				if(montage_has_finished(npc))
				{
					//icombat->Execute_melee_attack(npc);
					npc->melee_attack();
				}
			}
			
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return  EBTNodeResult::Succeeded;
	}
	return  EBTNodeResult::Failed;
}


bool UMeleeAttack::montage_has_finished(ANPC* const npc)
{
	return  npc->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npc->get_montage());
	
}
