// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LobbyPlayerInfo.h"
#include "PlayerListEntryWidget.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class EX_CPP_MULTIPLAYER_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	virtual void Update(const TArray<FLobbyPlayerInfo>& PlayerInfos);
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPlayerListEntryWidget> PlayerListEntryWidgetClass;
	
	UPROPERTY(meta=(BindWidget))
	class UButton* BackBtn;

	UPROPERTY(meta=(BindWidget))
	class UVerticalBox* PlayerListContainer;

	UPROPERTY(meta=(BindWidget))
	class UButton* ReadyBeginBtn;
		
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void OnBackBtn();

	UFUNCTION()
	virtual void OnReadyBegin();
};
