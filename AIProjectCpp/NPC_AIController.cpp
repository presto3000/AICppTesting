// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "AIProjectCppCharacter.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "blackboard_keys.h"
#include "Runtime/Engine//Classes//Kismet/GameplayStatics.h"
#include "Runtime//Engine/Classes//Engine/World.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"


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

void ANPC_AIController::on_updated(TArray<AActor*> const& updated_actors)
{

}

void ANPC_AIController::on_target_detected(AActor* actor, FAIStimulus const stimulus)
{
	if(auto const ch = Cast<AAIProjectCppCharacter>(actor))
	{
		get_blackboard()->SetValueAsBool(bb_keys::can_see_player, stimulus.WasSuccessfullySensed());
	}
}


void ANPC_AIController::setup_perception_system()
{
	//create and initialise sight configuration object
	sight_config = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	sight_config->SightRadius = 500.0f;
	sight_config->LoseSightRadius = sight_config ->SightRadius + 50.0f;
	sight_config->PeripheralVisionAngleDegrees = 90.0f;
	sight_config->SetMaxAge(5.0f);
	sight_config->AutoSuccessRangeFromLastSeenLocation = 900.0f;
	sight_config->DetectionByAffiliation.bDetectEnemies = true;
	sight_config->DetectionByAffiliation.bDetectFriendlies = true;
	sight_config->DetectionByAffiliation.bDetectNeutrals = true;

	//add sight configuration component ot perception component
	GetPerceptionComponent()->SetDominantSense(*sight_config->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ANPC_AIController::on_target_detected);
	GetPerceptionComponent()->ConfigureSense(*sight_config);
	
	
	
}


