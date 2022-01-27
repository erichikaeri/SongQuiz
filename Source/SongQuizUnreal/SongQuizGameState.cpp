// Fill out your copyright notice in the Description page of Project Settings.


#include "SongQuizGameState.h"

ASongQuizGameState::ASongQuizGameState()
{
	ChatComponent = CreateDefaultSubobject<UChatComponent>(TEXT("ChatComponent"));
	PlayerReadyTrackerComponent = CreateDefaultSubobject<UPlayerReadyTrackerComponent>(TEXT("PlayerReadyTrackerComponent"));
}

void ASongQuizGameState::MulticastSetSongListCsv_Implementation(const FString& CsvString)
{
	// TODO create song list
	OnSongListCreated.Broadcast(nullptr);
}

void ASongQuizGameState::MulticastOnNextSongDecided_Implementation(int32 SongNumber, int32 StartSeconds)
{
	OnNextSongDecided.Broadcast(SongNumber, StartSeconds);
}

void ASongQuizGameState::MulticastOnPlaySong_Implementation(int32 SongNumber)
{
	OnPlaySong.Broadcast(SongNumber);
}

void ASongQuizGameState::MulticastOnSongAnswered_Implementation(int32 SongNumber, APlayerState* Answerer)
{
	OnSongAnswered.Broadcast(SongNumber, Answerer);
}

void ASongQuizGameState::MulticastOnSongSkipped_Implementation(int32 SongNumber)
{
	OnSongSkipped.Broadcast(SongNumber);
}
