// Fill out your copyright notice in the Description page of Project Settings.


#include "SongQuizPlayerController.h"
#include "SongQuizGameState.h"

ASongQuizPlayerController::ASongQuizPlayerController()
{
}

void ASongQuizPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetNetMode() != NM_DedicatedServer)
	{
		ASongQuizGameState* GameState = GetWorld()->GetGameState<ASongQuizGameState>();
		check(IsValid(GameState));

		ClientChatComponent = GameState->ChatComponent;
		ClientChatComponent->OnChat.AddUObject(this, &ThisClass::ClientOnChatReceived);
	}
}

void ASongQuizPlayerController::ClientOnChatReceived(APlayerState* From, const FString& Message)
{
}
