// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseUnit.h"

#include "Components/PrimitiveComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "RTSController.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values
ABaseUnit::ABaseUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pDecal = CreateDefaultSubobject<UDecalComponent>(L"Decal");
	m_pDecal->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();

	m_pRTSController = Cast<ARTSController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -85));

	m_pDecal->SetMaterial(0, m_pDecalMaterial);
	m_pDecal->SetWorldRotation(FRotator(-90,0,0));
	m_pDecal->SetWorldScale3D(FVector(m_DecalScale.X, m_DecalScale.Y, m_DecalScale.Z));
	m_pDecal->SetVisibility(false);

	GetCharacterMovement()->MaxWalkSpeed = 1200;
}

// Called every frame
void ABaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseUnit::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	if (ButtonPressed == EKeys::LeftMouseButton)
	{
		if (m_pDecal->IsVisible())
		{
			if (m_pRTSController)
				m_pRTSController->RemoveUnitFromSelection(this);
		}

		else
		{
			if (m_pRTSController)
			{
				if (!m_pRTSController->IsMultiSelectEnabled())
					m_pRTSController->ClearSelection();

				m_pRTSController->AddUnitToSelection(this);
			}
				
		}
			
	}
	
}

void ABaseUnit::SetSelected(bool isSelected)
{
	m_pDecal->SetVisibility(isSelected);
}

UBlackboardComponent* ABaseUnit::GetBlackboardComponent()
{
	return m_pBlackboardComponent;
}

void ABaseUnit::SetBlackboardComponent(UBlackboardComponent* blackboardComp)
{
	if(blackboardComp)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("test"));
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("empty"));
	}
	m_pBlackboardComponent = blackboardComp;
}




