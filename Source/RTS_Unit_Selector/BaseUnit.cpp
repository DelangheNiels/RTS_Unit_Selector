// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseUnit.h"

#include "Components/PrimitiveComponent.h"

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
			m_pDecal->SetVisibility(false);

			if (m_pRTSController)
				m_pRTSController->RemoveUnitFromSelection(this);

		}

		else
		{
			m_pDecal->SetVisibility(true);

			if (m_pRTSController)
				m_pRTSController->AddUnitToSelection(this);
		}
			
	}
	
}




