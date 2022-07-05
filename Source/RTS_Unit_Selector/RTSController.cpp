// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSController.h"

#include "Components/InputComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


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
}

void ARTSController::AddUnitToSelection(ABaseUnit* unit)
{
	m_SelectedUnits.Add(unit);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(index));
}

void ARTSController::RemoveUnitFromSelection(ABaseUnit* unit)
{
	m_SelectedUnits.Remove(unit);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(m_SelectedUnits.Num()));
	
}

void ARTSController::StartSelection()
{
	if(m_pHud)
		m_pHud->StartSelection();
}

void ARTSController::EndSelection()
{
	if(m_pHud)
		m_pHud->StopSelection();
}

