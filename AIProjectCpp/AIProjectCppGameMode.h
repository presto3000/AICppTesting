// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NPC.h"
#include "AIProjectCppGameMode.generated.h"

UCLASS(minimalapi)
class AAIProjectCppGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AAIProjectCppGameMode();

	void BeginPlay() override;

private:
TSubclassOf<ANPC>FNPC_Class;
TSubclassOf<APatrolPath>FPatrolPath_Class;

};



