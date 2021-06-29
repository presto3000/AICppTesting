// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject//Interface.h"
#include "CombatInterface.generated.h"

/**
 * 
 */
UINTERFACE(Blueprintable)
class AIPROJECTCPP_API UCombatInterface : public UInterface
{
	GENERATED_BODY()
	
};

class AIPROJECTCPP_API ICombatInterface
{
	GENERATED_BODY()

	public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	int melee_attack();
	
};