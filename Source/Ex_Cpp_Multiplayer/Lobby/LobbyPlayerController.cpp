// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyPlayerController.h"

#include "LobbyGameMode.h"
#include "Ex_Cpp_Multiplayer/Ex_Cpp_Multiplayer.h"
#include "Blueprint/UserWidget.h"
#include "Ex_Cpp_Multiplayer/MyGameInstance.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		PlayerInfo.DisplayName = GetGameInstance<UMyGameInstance>()->GetOnlineDisplayName();

		ClientRPCCreateWidgets();
		ServerRPCOnPCReady(PlayerInfo);
	}
}

void ALobbyPlayerController::ClientRPCUpdateLobbyWidget_Implementation(const TArray<FLobbyPlayerInfo>& PlayerInfos)
{
	UE_LOG(LogMyGame, Display, TEXT("[Client] LobbyPlayerController::UpdateLobbyWidget"));
	UE_LOG(LogMyGame, Display, TEXT("[Client] PlayerInfos - %i"), PlayerInfos.Num());

	LobbyWidget->Update(PlayerInfos);
}

void ALobbyPlayerController::ClientRPCCreateWidgets_Implementation()
{
	// Show cursor
	SetShowMouseCursor(true);

	ensure(LobbyWidgetClass != nullptr);

	LobbyWidget = CreateWidget<ULobbyWidget>(this, LobbyWidgetClass, TEXT("LobbyWidget"));
	LobbyWidget->AddToViewport();
}

void ALobbyPlayerController::ServerRPCOnPCReady_Implementation(const FLobbyPlayerInfo& PInfo)
{
	PlayerInfo = PInfo;

	auto* GameMode = Cast<ALobbyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->OnPCReady(this);
}

void ALobbyPlayerController::ServerRPCSetClientIsReady_Implementation(bool bIsReady)
{
	PlayerInfo.IsReady = bIsReady;

	auto* GameMode = Cast<ALobbyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->UpdateClientLobbyWidgets();
}
