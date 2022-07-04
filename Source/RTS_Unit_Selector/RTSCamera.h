// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RTSCamera.generated.h"

UCLASS()
class RTS_UNIT_SELECTOR_API ARTSCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARTSCamera();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraMovement)
	float m_ScreenMovePercentage = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraMovement)
	float m_MovementSpeed = 100.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	APlayerController* m_pPlayerController;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void MoveCamera();
	void MoveLeft(float mousePosX, int32 viewportSizeX);
	void MoveRight(float mousePosX, int32 viewportSizeX);
	void MoveUp(float mousePosY, int32 viewportSizeY);
	void MoveDown(float mousePosY, int32 viewportSizeY);

	float NormalizeToRange(float value, float min, float max);

};
