// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LobbyPlayerInfo.h"
#include "LobbyPlayerController.h"
#include "GameFramework/GameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class EX_CPP_MULTIPLAYER_API ALobbyGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	virtual void OnPCReady(ALobbyPlayerController* PlayerController);

	virtual void UpdateClientLobbyWidgets();
	
protected:
	TArray<ALobbyPlayerController*> ConnectedPlayers;
	TArray<FLobbyPlayerInfo> ConnectedPlayerInfos;

	virtual void OnPostLogin(AController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
};
