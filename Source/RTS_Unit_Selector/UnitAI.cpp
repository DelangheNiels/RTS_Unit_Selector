// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitAI.h"
#include "BaseUnit.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AUnitAI::AUnitAI(const FObjectInitializer& objectInitializer)
{
	m_pBehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree Component"));
	m_pBlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

void AUnitAI::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);

	ABaseUnit* unit = Cast<ABaseUnit>(pawn);

	if (unit && unit->m_pBehaviorTree)
	{
		//Initialize blackboard
		m_pBlackboardComp->InitializeBlackboard(*unit->m_pBehaviorTree->BlackboardAsset);

		//Set blackboard keys
		m_TargetLocationKey = m_pBlackboardComp->GetKeyID("TargetLocation");

		unit->SetBlackboardComponent(m_pBlackboardComp);

		//Start BehaviorTree
		m_pBehaviorTreeComp->StartTree(*unit->m_pBehaviorTree);

	}
}
