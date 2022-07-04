// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSMarqueeHUD.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

ARTSMarqueeHUD::ARTSMarqueeHUD()
{

}

void ARTSMarqueeHUD::BeginPlay()
{
	Super::BeginPlay();
	
	m_IsDrawing = false;

	m_pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

void ARTSMarqueeHUD::DrawHUD()
{
	if (m_IsDrawing)
	{
		m_pPlayerController->GetMousePosition(m_EndPoint.X, m_EndPoint.Y);

		float width = m_EndPoint.X - m_StartPoint.X;
		float height = m_EndPoint.Y - m_StartPoint.Y;

		DrawRect(FLinearColor{ FVector4{255,156,247,0.5} }, m_StartPoint.X, m_StartPoint.Y, width, height);
	}
}

void ARTSMarqueeHUD::StartSelection()
{
	m_IsDrawing = true;
	m_pPlayerController->GetMousePosition(m_StartPoint.X, m_StartPoint.Y);
}

void ARTSMarqueeHUD::StopSelection()
{
	m_IsDrawing = false;
}
