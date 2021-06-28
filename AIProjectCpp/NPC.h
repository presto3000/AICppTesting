// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PatrolPath.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

UCLASS()
class AIPROJECTCPP_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();
	public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	APatrolPath* patrol_path;

	APatrolPath* get_patrol_path();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
