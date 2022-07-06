// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UnitAI.generated.h"

/**
 * 
 */

class UBehaviorTreeComponent;
class UBlackboardComponent;

UCLASS()
class RTS_UNIT_SELECTOR_API AUnitAI : public AAIController
{
	GENERATED_BODY()

public:
	AUnitAI(const FObjectInitializer& objectInitializer);

	virtual void OnPossess(APawn* pawn) override;

	UPROPERTY(EditAnywhere, Category = AI)
		UBehaviorTreeComponent* m_pBehaviorTreeComp;

	UPROPERTY(EditAnywhere, Category = AI)
		UBlackboardComponent* m_pBlackboardComp;
	
	//Blackboard keys
	uint8 m_TargetLocationKey;
};
