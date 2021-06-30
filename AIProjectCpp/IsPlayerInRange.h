// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "IsPlayerInRange.generated.h"

/**
 * 
 */
UCLASS()
class AIPROJECTCPP_API UIsPlayerInRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UIsPlayerInRange();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float melee_range = 25.0f;
	
	
	
};
