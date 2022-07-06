// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSController.h"

#include "Components/InputComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"


ARTSController::ARTSController()
{

}

void ARTSController::BeginPlay()
{
	m_pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (m_pPlayerController)
	{
		m_pHud = Cast<ARTSMarqueeHUD>(m_pPlayerController->GetHUD());
	}

	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	inputMode.SetHideCursorDuringCapture(false);
	SetInputMode(inputMode);
}

void ARTSController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	InputComponent->BindAction("DrawMarquee", IE_Pressed, this, &ARTSController::StartSelection);
	InputComponent->BindAction("DrawMarquee", IE_Released, this, &ARTSController::EndSelection);

	InputComponent->BindAction("SelectLocation", IE_Pressed, this, &ARTSController::SelectLocation);
}

void ARTSController::AddUnitToSelection(ABaseUnit* unit)
{
	m_SelectedUnits.Add(unit);
	unit->SetSelected(true);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(index));
}

void ARTSController::RemoveUnitFromSelection(ABaseUnit* unit)
{
	m_SelectedUnits.Remove(unit);
	unit->SetSelected(false);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(m_SelectedUnits.Num()));
	
}

void ARTSController::StartSelection()
{
	if (m_pHud)
	{
		ClearSelection();
		m_pHud->StartSelection();
		
	}
		
}

void ARTSController::EndSelection()
{
	if(m_pHud)
		m_pHud->StopSelection();
}

void ARTSController::ClearSelection()
{
	for(ABaseUnit* &unit : m_SelectedUnits)
	{
		unit->SetSelected(false);
	}

	m_SelectedUnits.Empty();
}

void ARTSController::SelectLocation()
{
	
	FHitResult hitResult;
	//Move to location when trace does not hit player
	if (!GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, true, hitResult))
	{

		//Get hit location
		GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, hitResult);

		for (auto& unit : m_SelectedUnits)
		{
			if (unit->GetBlackboardComponent())
			{
				unit->GetBlackboardComponent()->SetValueAsVector("TargetLocation", hitResult.Location);
			}
				
		}
	}
}

