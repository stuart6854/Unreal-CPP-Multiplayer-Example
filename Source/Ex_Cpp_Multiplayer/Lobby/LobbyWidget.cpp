// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"

#include "LobbyPlayerController.h"
#include "PlayerListEntryWidget.h"
#include "Ex_Cpp_Multiplayer/Ex_Cpp_Multiplayer.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Ex_Cpp_Multiplayer/MyGameInstance.h"

void ULobbyWidget::Update(const TArray<FLobbyPlayerInfo>& PlayerInfos)
{
	PlayerListContainer->ClearChildren();
	for (auto Player : PlayerInfos)
	{
		UE_LOG(LogMyGame, Display, TEXT("%s"), *Player.DisplayName);

		auto* PlayerEntryWidget = CreateWidget<UPlayerListEntryWidget>(this, PlayerListEntryWidgetClass);
		PlayerEntryWidget->SetPlayerInfo(Player);
		PlayerListContainer->AddChild(PlayerEntryWidget);
	}
}

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BackBtn->OnClicked.AddUniqueDynamic(this, &ULobbyWidget::OnBackBtn);

	ReadyBeginBtn->OnClicked.AddUniqueDynamic(this, &ULobbyWidget::OnReadyBegin);
}

void ULobbyWidget::OnBackBtn()
{
	GetGameInstance<UMyGameInstance>()->LeaveServer();
}

void ULobbyWidget::OnReadyBegin()
{
	if (GetOwningPlayer()->IsNetMode(NM_ListenServer))
	{
		// Host
	}
	else if (GetOwningPlayer()->IsNetMode(NM_Client))
	{
		// Client
		auto* PC = GetOwningPlayer<ALobbyPlayerController>();
		PC->SetIsReady(!PC->GetIsReady());
	}
}
