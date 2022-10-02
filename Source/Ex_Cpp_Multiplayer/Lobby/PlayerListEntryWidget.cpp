// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerListEntryWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UPlayerListEntryWidget::SetPlayerInfo(const FLobbyPlayerInfo& PlayerInfo)
{
	if (NameLabel != nullptr)
	{
		NameLabel->SetText(FText::FromString(PlayerInfo.DisplayName));
	}

	if (ReadyLabel != nullptr)
	{
		if (PlayerInfo.IsReady)
		{
			ReadyLabel->SetText(NSLOCTEXT("Namespace", "key", "Ready"));
		}
		else
		{
			ReadyLabel->SetText(NSLOCTEXT("Namespace", "key", "Not ready"));
		}
	}
}

void UPlayerListEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
