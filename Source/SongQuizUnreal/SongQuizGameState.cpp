// Fill out your copyright notice in the Description page of Project Settings.


#include "SongQuizGameState.h"

USongList* USongList::New(UObject* Owner, const FString& CsvString)
{
	USongList* Ret = NewObject<USongList>(Owner);

	// Parse Csv

	return Ret;
}

const USongList::FSong& USongList::GetSong(int32 SongNumber) const
{
	if (!Songs.IsValidIndex(SongNumber))
	{
		return {};
	}

	return Songs[SongNumber];
}

int32 USongList::GetCurrentSongNumber() const
{
	return CurrentSongNumber;
}

TOptional<int32> USongList::NextSequential()
{
	int32 NextSongNumber = CurrentSongNumber + 1;
	while (PlayedSongs.Contains(NextSongNumber))
	{
		NextSongNumber++;
	}

	if (!NotPlayedSongs.Contains(NextSongNumber))
	{
		return {};
	}

	NotPlayedSongs.Remove(NextSongNumber);
	PlayedSongs.Add(NextSongNumber);
	CurrentSongNumber = NextSongNumber;

	return CurrentSongNumber;
}

TOptional<int32> USongList::NextRandom()
{
	if (NotPlayedSongs.Num() == 0)
	{
		return {};
	}

	const int32 IterCount = FMath::RandRange(0, NotPlayedSongs.Num() - 1);
	auto Iter = NotPlayedSongs.CreateConstIterator();
	for (int32 i = 0; i < IterCount; i++)
	{
		++Iter;
	}

	CurrentSongNumber = Iter->Key;

	return CurrentSongNumber;
}

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
