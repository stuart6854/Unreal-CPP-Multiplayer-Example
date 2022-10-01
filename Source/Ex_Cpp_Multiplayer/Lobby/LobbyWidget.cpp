// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"

#include "Components/Button.h"
#include "Ex_Cpp_Multiplayer/MyGameInstance.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BackBtn->OnClicked.AddUniqueDynamic(this, &ULobbyWidget::OnBackBtn);
}

void ULobbyWidget::OnBackBtn()
{
	GetGameInstance<UMyGameInstance>()->LeaveServer();
}
