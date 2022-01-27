// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChatComponent.h"
#include "GameFramework/PlayerController.h"
#include "SongQuizPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SONGQUIZUNREAL_API ASongQuizPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASongQuizPlayerController();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UChatComponent* ClientChatComponent;

	void ClientOnChatReceived(APlayerState* From, const FString& Message);
	void ClientOnPlayerReady(APlayerState* ReadyPlayer);
};
