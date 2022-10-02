// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

#include "Ex_Cpp_Multiplayer.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Kismet/GameplayStatics.h"

static const FName SESSION_DISCONNECT_LEVEL = "/Game/_Project/Levels/Lvl_MainMenu";
static const FName SESSION_LOBBY_LEVEL = "/Game/_Project/Levels/Lvl_Lobby";

static const FName SESSION_NAME = "Stuart6854SessionName";

void UMyGameInstance::Init()
{
	if (const IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		SessionInterface = Subsystem->GetSessionInterface();
		if (!SessionInterface.IsValid())
		{
			UE_LOG(LogMyGame, Error, TEXT("Failed to get Online Session Interface!"));
		}

		SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMyGameInstance::OnSessionCreateComplete);
		SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UMyGameInstance::OnSessionDestroyComplete);
		SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UMyGameInstance::OnFindSessionsComplete);
		SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UMyGameInstance::OnJoinSessionComplete);

		IdentityInterface = Subsystem->GetIdentityInterface();
		if (!IdentityInterface.IsValid())
		{
			UE_LOG(LogMyGame, Error, TEXT("Failed to get Online Identity Interface!"));
		}
	}
	else
	{
		UE_LOG(LogMyGame, Error, TEXT("Failed to get Online Subsystem!"));
	}
}

void UMyGameInstance::Shutdown()
{
	if (SessionActive)
	{
		SessionInterface->DestroySession(ActiveSessionName);
	}
}

void UMyGameInstance::CreateServer() const
{
	UE_LOG(LogMyGame, Display, TEXT("Creating Server..."));

	FOnlineSessionSettings Settings;
	Settings.bAllowJoinInProgress = true;
	Settings.bIsDedicated = false;
	Settings.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL"; // TODO: Lobby Setting?
	Settings.bShouldAdvertise = true; // TODO: Lobby Setting
	Settings.bUsesPresence = true;
	Settings.bUseLobbiesIfAvailable = true; // Note: This allows SteamWorks to work (I believe)
	Settings.NumPublicConnections = 5; // TODO: Lobby Setting
	// Settings.NumPrivateConnections = 5; // TODO: Lobby Setting
	SessionInterface->CreateSession(0, SESSION_NAME, Settings);
}

void UMyGameInstance::JoinServer()
{
	UE_LOG(LogMyGame, Display, TEXT("Joining Server..."));

	SearchSettings = MakeShareable(new FOnlineSessionSearch());
	SearchSettings->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL"; // TODO: Lobby Setting?
	SearchSettings->MaxSearchResults = 10;
	SearchSettings->QuerySettings.Set("SEARCH_PRESENCE", true, EOnlineComparisonOp::Equals);

	SessionInterface->FindSessions(0, SearchSettings.ToSharedRef());
}

void UMyGameInstance::LeaveServer() const
{
	UE_LOG(LogMyGame, Display, TEXT("Leaving Server..."));

	if (SessionActive)
	{
		SessionInterface->DestroySession(ActiveSessionName);
	}
}

FString UMyGameInstance::GetOnlineDisplayName() const
{
	return IdentityInterface->GetPlayerNickname(0);
}

void UMyGameInstance::OnSessionCreateComplete(const FName SessionName, const bool Success)
{
	if (!Success)
	{
		UE_LOG(LogMyGame, Error, TEXT("Failed to create Session!"));
		return;
	}
	UE_LOG(LogMyGame, Display, TEXT("Session created."));

	this->SessionActive = true;
	this->ActiveSessionName = SessionName;

	// UGameplayStatics::OpenLevel(GetWorld(), SESSION_LOBBY_LEVEL, true, "listen");
	GetWorld()->ServerTravel("/Game/_Project/Levels/Lvl_Lobby?listen");
}

void UMyGameInstance::OnSessionDestroyComplete(const FName SessionName, const bool Success)
{
	if (!Success)
	{
		UE_LOG(LogMyGame, Error, TEXT("Failed to destroy Session!"));
		return;
	}
	UE_LOG(LogMyGame, Display, TEXT("Session destroyed."));

	this->SessionActive = false;
	this->ActiveSessionName = "";

	// Throw client to level
	UGameplayStatics::OpenLevel(GetWorld(), SESSION_DISCONNECT_LEVEL);
}

void UMyGameInstance::OnFindSessionsComplete(const bool Success) const
{
	if (!Success)
	{
		UE_LOG(LogMyGame, Error, TEXT("Failed to find sessions!"));
		return;
	}

	const auto& SearchResults = SearchSettings->SearchResults;
	if (SearchResults.IsEmpty())
	{
		UE_LOG(LogMyGame, Warning, TEXT("No sessions found."), SearchResults.Num());
		return;
	}
	UE_LOG(LogMyGame, Display, TEXT("Found %i sessions."), SearchResults.Num());

	// TEMP: Join first search result
	const auto& SessionToJoin = SearchResults[0];
	SessionInterface->JoinSession(0, SESSION_NAME, SessionToJoin);
}

void UMyGameInstance::OnJoinSessionComplete(const FName SessionName, const EOnJoinSessionCompleteResult::Type Result)
{
	if (Result != EOnJoinSessionCompleteResult::Success)
	{
		UE_LOG(LogMyGame, Error, TEXT("Failed to join session!"));
		return;
	}
	UE_LOG(LogMyGame, Display, TEXT("Session joined."));

	this->SessionActive = true;
	this->ActiveSessionName = SessionName;

	auto* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FString TravelUrl;
	if (PlayerController && SessionInterface->GetResolvedConnectString(SessionName, TravelUrl))
	{
		UE_LOG(LogMyGame, Display, TEXT("TravelUrl=<%s>"), *TravelUrl);
		PlayerController->ClientTravel(TravelUrl, TRAVEL_Absolute);
	}
}
