// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTSController.generated.h"

/**
 * 
 */
UCLASS()
class RTS_UNIT_SELECTOR_API ARTSController : public APlayerController
{
	GENERATED_BODY()

public:
	ARTSController();


protected:
	virtual void BeginPlay() override;


private:
	FInputModeGameAndUI inputMode;
	
};
