// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class EX_CPP_MULTIPLAYER_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta=(BindWidget))
	class UButton* BackBtn;

	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void OnBackBtn();
};
