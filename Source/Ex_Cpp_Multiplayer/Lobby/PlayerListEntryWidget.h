// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LobbyPlayerInfo.h"
#include "Blueprint/UserWidget.h"
#include "PlayerListEntryWidget.generated.h"

/**
 * 
 */
UCLASS()
class EX_CPP_MULTIPLAYER_API UPlayerListEntryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION()
	virtual void SetPlayerInfo(const FLobbyPlayerInfo& PlayerInfo);

protected:
	UPROPERTY(meta=(BindWidget))
	class UImage* IconImage;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* NameLabel;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ReadyLabel;

	virtual void NativeConstruct() override;
};
