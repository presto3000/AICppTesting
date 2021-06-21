// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "AIProjectCppCharacter.h"


ANPC_AIController::ANPC_AIController(FObjectInitializer const& object_initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>obj(TEXT("BehaviorTree'/Game/AI/NPC_BT.NPC_BT'"));
	if(obj.Succeeded())
	{
		btree = obj.Object;
	}
	behavior_tree_component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
	
}

void ANPC_AIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(btree);
	behavior_tree_component->StartTree(*btree);
	
}

void ANPC_AIController::OnPossess(APawn* const InPawn)
{
	Super::OnPossess(InPawn);
	if(blackboard)
	{
		blackboard->InitializeBlackboard(*btree->BlackboardAsset);
	}
	
}

UBlackboardComponent* ANPC_AIController::get_blackboard() const
{
	return blackboard;
}
