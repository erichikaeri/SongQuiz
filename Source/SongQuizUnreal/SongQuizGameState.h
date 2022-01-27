// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChatComponent.h"
#include "PlayerReadyTrackerComponent.h"
#include "GameFramework/GameStateBase.h"
#include "SongQuizGameState.generated.h"

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
