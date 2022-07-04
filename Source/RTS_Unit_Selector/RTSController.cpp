// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSController.h"

ARTSController::ARTSController()
{

}

void ARTSController::BeginPlay()
{
	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	inputMode.SetHideCursorDuringCapture(false);
	SetInputMode(inputMode);
}
