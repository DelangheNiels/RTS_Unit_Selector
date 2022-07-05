// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "RTSMarqueeHUD.h"
#include "BaseUnit.h"

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

	virtual void SetupInputComponent() override;

private:
	FInputModeGameAndUI inputMode;
	
	APlayerController* m_pPlayerController;

	ARTSMarqueeHUD* m_pHud;

	TArray<ABaseUnit*> m_SelectedUnits{};

public:
	void AddUnitToSelection(ABaseUnit* unit);
	void RemoveUnitFromSelection(ABaseUnit* unit);

private:

	void StartSelection();
	void EndSelection();
};
