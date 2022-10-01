// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyPlayerController.h"

#include "Blueprint/UserWidget.h"

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CreateWidgets();
}

void ALobbyPlayerController::CreateWidgets_Implementation()
{
	// Show cursor
	SetShowMouseCursor(true);

	ensure(LobbyWidgetClass != nullptr);
	
	LobbyWidget = CreateWidget<ULobbyWidget>(this, LobbyWidgetClass, TEXT("LobbyWidget"));
	LobbyWidget->AddToViewport();
}
