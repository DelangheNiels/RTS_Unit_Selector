// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSCamera.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values
ARTSCamera::ARTSCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARTSCamera::BeginPlay()
{
	Super::BeginPlay();

	m_pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//set this camera as view camera
	m_pPlayerController->SetViewTargetWithBlend(this);

	SetActorRotation(FRotator(0, 90, 0));
	
}

// Called every frame
void ARTSCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveCamera();

}

void ARTSCamera::MoveCamera()
{
	float mousePosX{}, mousePosY{};
	m_pPlayerController->GetMousePosition(mousePosX, mousePosY);

	int32 viewportSizeX{}, viewportSizeY{};
	m_pPlayerController->GetViewportSize(viewportSizeX, viewportSizeY);

	MoveLeft(mousePosX, viewportSizeX);
	MoveRight(mousePosX, viewportSizeX);
	MoveUp(mousePosY, viewportSizeY);
	MoveDown(mousePosY, viewportSizeY);
}

void ARTSCamera::MoveLeft(float mousePosX, int32 viewportSizeX)
{
	//speed up camera movement when closer to screen border
	float speed = NormalizeToRange(mousePosX, 0, viewportSizeX * m_ScreenMovePercentage);
	speed = FMath::Clamp<float>(speed, 0, 1);
	speed = 1 - speed;

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%f"), speed));
	FVector movementVector = FVector(m_MovementSpeed, 0, 0);
	movementVector *= speed;

	SetActorLocation(GetActorLocation() + movementVector);
}

void ARTSCamera::MoveRight(float mousePosX, int32 viewportSizeX)
{
	float speed = NormalizeToRange(mousePosX, viewportSizeX * (1 - m_ScreenMovePercentage),viewportSizeX);
	speed = FMath::Clamp<float>(speed, 0, 1);

	FVector movementVector = FVector(-m_MovementSpeed, 0, 0);
	movementVector *= speed;

	SetActorLocation(GetActorLocation() + movementVector);
}

void ARTSCamera::MoveUp(float mousePosY, int32 viewportSizeY)
{
	float speed = NormalizeToRange(mousePosY, 0, viewportSizeY * m_ScreenMovePercentage);
	speed = FMath::Clamp<float>(speed, 0, 1);
	speed = 1 - speed;

	FVector movementVector = FVector(0, m_MovementSpeed, 0);
	movementVector *= speed;

	SetActorLocation(GetActorLocation() + movementVector);
}

void ARTSCamera::MoveDown(float mousePosY, int32 viewportSizeY)
{
	float speed = NormalizeToRange(mousePosY, viewportSizeY * (1 - m_ScreenMovePercentage), viewportSizeY);
	speed = FMath::Clamp<float>(speed, 0, 1);

	FVector movementVector = FVector(0, -m_MovementSpeed, 0);
	movementVector *= speed;

	SetActorLocation(GetActorLocation() + movementVector);
}

float ARTSCamera::NormalizeToRange(float value, float min, float max)
{
	if (max > min)
	{
		
		float range = max - min;

		return (value - min) / range;
		
	}

	return 0;
	
}

