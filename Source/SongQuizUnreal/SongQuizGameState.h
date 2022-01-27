// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChatComponent.h"
#include "PlayerReadyTrackerComponent.h"
#include "GameFramework/GameStateBase.h"
#include "SongQuizGameState.generated.h"

UCLASS()
class USongList : public UObject
{
	GENERATED_BODY()

public:
	struct FSong
	{
		FString Name;
		FString Artist;
		TOptional<FString> Show;
		TArray<FString> AcceptableAnswers;
	};

	static USongList* New(UObject* Owner, const FString& CsvString);

	const FSong& GetSong(int32 SongNumber) const;
	int32 GetCurrentSongNumber() const;

	TOptional<int32> NextSequential();
	TOptional<int32> NextRandom();

private:
	int32 CurrentSongNumber = 0;
	TArray<FSong> Songs;
	TMap<int32, FSong*> PlayedSongs;
	TMap<int32, FSong*> NotPlayedSongs;
};

/**
 * 
 */
UCLASS()
class SONGQUIZUNREAL_API ASongQuizGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ASongQuizGameState();

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnSongListCreated, UObject*);
	FOnSongListCreated OnSongListCreated;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnNextSongDecided, int32, int32);
	FOnNextSongDecided OnNextSongDecided;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlaySong, int32);
	FOnPlaySong OnPlaySong;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSongAnswered, int32, APlayerState*);
	FOnSongAnswered OnSongAnswered;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnSongSkipped, int32);
	FOnSongSkipped OnSongSkipped;

	UPROPERTY()
	UChatComponent* ChatComponent;

	UPROPERTY()
	UPlayerReadyTrackerComponent* PlayerReadyTrackerComponent;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastSetSongListCsv(const FString& CsvString);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnNextSongDecided(int32 SongNumber, int32 StartSeconds);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnPlaySong(int32 SongNumber);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnSongAnswered(int32 SongNumber, APlayerState* Answerer);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnSongSkipped(int32 SongNumber);
};
