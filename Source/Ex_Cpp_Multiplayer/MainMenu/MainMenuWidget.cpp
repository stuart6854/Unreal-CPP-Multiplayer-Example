// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuWidget.h"
#include "Ex_Cpp_Multiplayer/MyGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CreateServerBtn->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnCreateServer);
	JoinServerBtn->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnJoinServer);
	ExitBtn->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnExit);
}

void UMainMenuWidget::OnCreateServer()
{
	auto* GameInstance = GetGameInstance<UMyGameInstance>();
	GameInstance->CreateServer();
}

void UMainMenuWidget::OnJoinServer()
{
	auto* GameInstance = GetGameInstance<UMyGameInstance>();
	GameInstance->JoinServer();
}

void UMainMenuWidget::OnExit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
