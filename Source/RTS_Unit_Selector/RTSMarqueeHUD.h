// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTSMarqueeHUD.generated.h"

/**
 * 
 */

class ABaseUnit;
class ARTSController;

UCLASS()
class RTS_UNIT_SELECTOR_API ARTSMarqueeHUD : public AHUD
{
	GENERATED_BODY()

public:
	ARTSMarqueeHUD();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MarqueeColor)
		FVector4 m_MarqueeColor;

protected:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

private:
	bool m_IsDrawing{};

	FVector2D m_StartPoint{}, m_EndPoint{};

	ARTSController* m_pRTSController;

	TArray<ABaseUnit*> m_SelectedUnits{};

public:

	void StartSelection();
	void StopSelection();
	
};
