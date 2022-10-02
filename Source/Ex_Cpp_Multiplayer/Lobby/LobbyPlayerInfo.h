#pragma once

#include "LobbyPlayerInfo.generated.h"

USTRUCT(BlueprintType)
struct FLobbyPlayerInfo
{
	GENERATED_BODY()

	UPROPERTY()
	FString DisplayName = "$DisplayName";
	UPROPERTY()
	bool IsReady = false;

	FORCEINLINE bool operator==(const FLobbyPlayerInfo& Other) const
	{
		return DisplayName.Equals(Other.DisplayName);
	}
};
