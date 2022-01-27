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

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnSongListReceived, const FString&);
	FOnSongListReceived OnSongListReceived;

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

private:
	friend class ASongQuizGameMode;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnSongListReceived();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnNextSongDecided();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnPlaySong();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnSongAnswered();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnSongSkipped();
};
