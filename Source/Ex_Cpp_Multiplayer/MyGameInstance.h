// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class EX_CPP_MULTIPLAYER_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;
	virtual void Shutdown() override;

	void CreateServer() const;
	void JoinServer();

	void LeaveServer() const;

	FString GetOnlineDisplayName() const;

protected:
	IOnlineSessionPtr SessionInterface = nullptr;
	IOnlineIdentityPtr IdentityInterface = nullptr;

	TSharedPtr<class FOnlineSessionSearch> SearchSettings;

	bool SessionActive = false;
	FName ActiveSessionName = "";

	void OnSessionCreateComplete(FName SessionName, bool Success);
	void OnSessionDestroyComplete(FName SessionName, bool Success);
	void OnFindSessionsComplete(bool Success) const;
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
};
