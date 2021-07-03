#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPC_AIController.generated.h"


UCLASS()
class AIPROJECTCPP_API ANPC_AIController : public AAIController
{
	GENERATED_BODY()
	public:	
	ANPC_AIController(FObjectInitializer const& object_initializer = FObjectInitializer::Get());
	void BeginPlay() override;

	void OnPossess(APawn* const pawn) override;
	//class UBlackboardComponent* get_blackboard() const;
	private:
	//UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	//class UBehaviorTreeComponent* behavior_tree_component;

	//UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	//class UBehaviorTree* btree;
	UPROPERTY()
	class UBlackboardComponent* BlackboardComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UAISenseConfig_Sight* sight_config;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UAISenseConfig_Hearing* hearing_config;

	UFUNCTION()
	void on_updated(TArray<AActor*> const& updated_actors);

	void setup_perception_system();
};