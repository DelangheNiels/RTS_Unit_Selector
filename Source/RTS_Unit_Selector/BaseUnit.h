// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/DecalComponent.h"
#include "Runtime/Engine/Classes/Engine/DecalActor.h"

#include "BaseUnit.generated.h"


class ARTSController;
class UBehaviorTree;
class UBlackboardComponent;

UCLASS()
class RTS_UNIT_SELECTOR_API ABaseUnit : public ACharacter
{
	GENERATED_BODY()

public:
	
	ABaseUnit();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Decals)
		UMaterialInstance* m_pDecalMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Decals)
		FVector m_DecalScale;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI)
		UBehaviorTree* m_pBehaviorTree;


private:

	UDecalComponent* m_pDecal;

	ARTSController* m_pRTSController;

	UBlackboardComponent* m_pBlackboardComponent;


protected:
	
	virtual void BeginPlay() override;


public:	
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;

	void SetSelected(bool isSelected);

	UBlackboardComponent* GetBlackboardComponent();
	void SetBlackboardComponent(UBlackboardComponent* blackboardComp);

};
