// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPC_AIController.generated.h"

/**
 * 
 */
UCLASS()
class AIPROJECTCPP_API ANPC_AIController : public AAIController
{
	GENERATED_BODY()

/**Constructor of Single argument of FObject Init */
public:
	ANPC_AIController(FObjectInitializer const& object_initializer = FObjectInitializer::Get());
/** Void BeginPlay*/
	void BeginPlay() override;

	void OnPossess(APawn* const InPawn) override;
	class UBlackboardComponent* get_blackboard() const;
private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* behavior_tree_component;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* btree;

	class UBlackboardComponent* blackboard;
	
};
