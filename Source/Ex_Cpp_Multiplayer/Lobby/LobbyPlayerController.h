// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LobbyPlayerInfo.h"
#include "LobbyWidget.h"
#include "LobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class EX_CPP_MULTIPLAYER_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	
	UFUNCTION(Client, Reliable)
	virtual void ClientRPCUpdateLobbyWidget(const TArray<FLobbyPlayerInfo>& PlayerInfos);

	FLobbyPlayerInfo& GetPlayerInfo() { return PlayerInfo; }

protected:
	UPROPERTY(BlueprintReadWrite)
	FLobbyPlayerInfo PlayerInfo;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> LobbyWidgetClass;

	ULobbyWidget* LobbyWidget;

	UFUNCTION(Client, Reliable)
	virtual void ClientRPCCreateWidgets();
	
	UFUNCTION(Server, Reliable)
	virtual void ServerRPCOnPCReady(const FLobbyPlayerInfo& PInfo);
};
