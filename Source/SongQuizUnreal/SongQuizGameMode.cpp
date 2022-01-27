// Copyright Epic Games, Inc. All Rights Reserved.


#include "SongQuizGameMode.h"
#include "SongQuizPlayerController.h"

ASongQuizGameMode::ASongQuizGameMode()
{
	GameStateClass = ASongQuizGameState::StaticClass();
	PlayerControllerClass = ASongQuizPlayerController::StaticClass();
}

void ASongQuizGameMode::PlayNextSong()
{
	SongQuizGameState->MulticastOnPlaySong(0);
}

void ASongQuizGameMode::BeginPlay()
{
	Super::BeginPlay();

	SongQuizGameState = GetGameState<ASongQuizGameState>();
	SongQuizGameState->PlayerReadyTrackerComponent->OnAllPlayersReady.AddUObject(this, &ThisClass::PlayNextSong);
}
