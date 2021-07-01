// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "ChangeSpeedService.generated.h"

/**
 * 
 */
UCLASS()
class AIPROJECTCPP_API UChangeSpeedService : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	public:
	UChangeSpeedService();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	FString GetStaticServiceDescription() const override;

	private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float speed = 600.f;
	
};
