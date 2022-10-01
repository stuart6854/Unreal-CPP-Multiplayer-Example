// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> LobbyWidgetClass;

	ULobbyWidget* LobbyWidget;
	
	UFUNCTION(Client, Reliable)
	virtual void CreateWidgets();
};
