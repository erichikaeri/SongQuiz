// Fill out your copyright notice in the Description page of Project Settings.


#include "SongQuizGameState.h"

ASongQuizGameState::ASongQuizGameState()
{
	ChatComponent = CreateDefaultSubobject<UChatComponent>(TEXT("ChatComponent"));
}

void ASongQuizGameState::MulticastOnSongListReceived_Implementation()
{
	OnSongListReceived.Broadcast({});
}

void ASongQuizGameState::MulticastOnNextSongDecided_Implementation()
{
	OnNextSongDecided.Broadcast({}, {});
}

void ASongQuizGameState::MulticastOnPlaySong_Implementation()
{
	OnPlaySong.Broadcast({});
}

void ASongQuizGameState::MulticastOnSongAnswered_Implementation()
{
	OnSongAnswered.Broadcast({}, {});
}

void ASongQuizGameState::MulticastOnSongSkipped_Implementation()
{
	OnSongSkipped.Broadcast({});
}
