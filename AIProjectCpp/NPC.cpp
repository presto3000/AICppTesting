// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/PlayerController.h"

#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.h"

#include "Components/BoxComponent.h"
#include "AIProjectCppCharacter.h"

// Sets default values
ANPC::ANPC() :
	
	widget_widgets(CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"))),
	health(max_health)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;
	//GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;

		if(widget_widgets)
	{
		widget_widgets->SetupAttachment(RootComponent);
		widget_widgets->SetWidgetSpace(EWidgetSpace::Screen);
		widget_widgets->SetRelativeLocation(FVector(0.0f, 0.0f, 85.0f));
		static ConstructorHelpers::FClassFinder<UUserWidget> widget_class(TEXT("/Game/UI/HealthBar_BP"));
		if(widget_class.Succeeded())
		{
			widget_widgets->SetWidgetClass(widget_class.Class);


		}


	}
	
}

APatrolPath* ANPC::get_patrol_path()
{
	return patrol_path;
}

void ANPC::melee_attack()
{
	if(montage)
	{
		PlayAnimMontage(montage);
	}
}
/** 
int ANPC::melee_attack_Implementation()
{
	if(montage)
	{
		PlayAnimMontage(montage);
		
	}
	return 0;
}
*/

UAnimMontage* ANPC::get_montage() const
{
	return  montage;
}

float ANPC::get_health()const 
{
	return health;
}

float ANPC::get_max_health()const 
{
	return max_health;	
}

void ANPC::set_health(float const new_health) 
{
	health = new_health;	
	if(health <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("You Win You GEnius!!!"));
		GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");

	}
}

UBehaviorTree* ANPC::GetBehaviorTree() const {
	return BehaviorTree;
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	/** Set material color of NPC */
	UMaterialInstanceDynamic* const material_instance = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), this);
	if(material_instance)
	{
		material_instance->SetVectorParameterValue("BodyColor", FLinearColor(1.0f, 0.0f, 0, 1.0f));
		GetMesh()->SetMaterial(0, material_instance);
	}


}
void ANPC::on_attack_overlap_begin(
		UPrimitiveComponent* const overlapped_component,
		AActor* const other_actor,
		UPrimitiveComponent* other_component,
		int const other_body_index,
		bool const from_sweep,
		FHitResult const& sweep_result) 
		{
				if(AAIProjectCppCharacter* const player = Cast <AAIProjectCppCharacter>(other_actor))
				{
					float const new_health = player->get_health() - player->get_max_health() * 0.07f;
					player->set_health(new_health);
				}
	
		}
void ANPC::on_attack_overlap_end(
		UPrimitiveComponent* const overlapped_component,
		AActor* const other_actor,
		UPrimitiveComponent* other_component,
		int const other_body_index)
		{
	
		}
			


// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto const uw = Cast<UHealthBar>(widget_widgets->GetUserWidgetObject());
	if(uw)
	{
		uw->set_bar_value_percent(health/max_health);

	}
}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

