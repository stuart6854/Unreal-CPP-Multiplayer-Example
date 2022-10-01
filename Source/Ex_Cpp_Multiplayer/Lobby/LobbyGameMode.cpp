// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"

#include "Ex_Cpp_Multiplayer/Ex_Cpp_Multiplayer.h"
#include "GameFramework/PlayerState.h"

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
}
