// Copyright Epic Games, Inc. All Rights Reserved.

#include "AIProjectCppGameMode.h"
#include "AIProjectCppCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAIProjectCppGameMode::AAIProjectCppGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<ANPC> npc(TEXT("Blueprint'/Game/AI/NPC_BP'"));
	if(npc.Succeeded())
	{
		FNPC_Class = npc.Class;
	}
	static ConstructorHelpers::FClassFinder<APatrolPath>Patrol(TEXT("Blueprint'/Game/AI/PatrolPath_BP'"));
	if(Patrol.Succeeded())
	{
		FPatrolPath_Class = Patrol.Class;
	}
}	

void AAIProjectCppGameMode::BeginPlay()
{
	Super::BeginPlay();
	if(FNPC_Class && FPatrolPath_Class)
	{
		FVector const NPC_loc{-800, 400,226};
		FVector const PatrolPath_loc {-600, -900, 130.f};
		FActorSpawnParameters const params;
		if (auto const path = GetWorld()->SpawnActor<APatrolPath>(FPatrolPath_Class, PatrolPath_loc, FRotator::ZeroRotator, params))
		{
			path->AddPatrolPoint(FVector{0.f, 0.f, 0.f});			
			path->AddPatrolPoint(FVector{1550.f, -30.f, 0.f});			
			path->AddPatrolPoint(FVector{1580.f, 2290.f, 0.f});			
			path->AddPatrolPoint(FVector{90.f, 2350.f, 0.f});			
			path->AddPatrolPoint(FVector{0.f, 1150.f, 0.f});
			if (auto const NPC = GetWorld()->SpawnActor<ANPC>(FNPC_Class, NPC_loc, FRotator::ZeroRotator, params))
			{
				NPC->SetPatrolPath(path);
			}
		}
	}
}
