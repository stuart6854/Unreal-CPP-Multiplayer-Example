// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"

#include "Ex_Cpp_Multiplayer/Ex_Cpp_Multiplayer.h"
#include "GameFramework/PlayerState.h"

void ALobbyGameMode::OnPCReady(ALobbyPlayerController* PlayerController)
{
	ConnectedPlayers.Add(PlayerController);

	UpdateClientLobbyWidgets();
}

void ALobbyGameMode::UpdateClientLobbyWidgets()
{
	ConnectedPlayerInfos.Empty();
	for (auto* Player : ConnectedPlayers)
	{
		ConnectedPlayerInfos.Add(Player->GetPlayerInfo());
	}

	// Update all client Lobby widgets
	for (auto* Player : ConnectedPlayers)
	{
		Player->ClientRPCUpdateLobbyWidget(ConnectedPlayerInfos);
	}
}

void ALobbyGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	const auto* PlayerState = NewPlayer->GetPlayerState<APlayerState>();
	const FString PlayerName = PlayerState->GetPlayerName();

	UE_LOG(LogMyGame, Display, TEXT("[GameMode] OnPostLogin - %s"), *PlayerName);
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	UE_LOG(LogMyGame, Display, TEXT("[GameMode] Logout"));

	auto* LobbyPC = Cast<ALobbyPlayerController>(Exiting);
	ConnectedPlayers.Remove(LobbyPC);
	ConnectedPlayerInfos.Remove(LobbyPC->GetPlayerInfo());

	for (auto* Player : ConnectedPlayers)
	{
		Player->ClientRPCUpdateLobbyWidget(ConnectedPlayerInfos);
	}
}
