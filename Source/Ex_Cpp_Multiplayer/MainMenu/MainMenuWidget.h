// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class EX_CPP_MULTIPLAYER_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta=(BindWidget))
	class UButton* CreateServerBtn;

	UPROPERTY(meta=(BindWidget))
	class UButton* JoinServerBtn;

	UPROPERTY(meta=(BindWidget))
	class UButton* ExitBtn;

	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void OnCreateServer();
	UFUNCTION()
	virtual void OnJoinServer();
	UFUNCTION()
	virtual void OnExit();
};
