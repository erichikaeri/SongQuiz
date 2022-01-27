// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerReadyTrackerComponent.h"

void UPlayerReadyTrackerComponent::SetPlayersToWaitFor(const TArray<APlayerController*>& PlayerList)
{
	check(GetNetMode() != NM_Client);

	Players.Empty();
	for (APlayerController* Each : PlayerList)
	{
		Players.FindOrAdd(Each) = false;
	}
}

void UPlayerReadyTrackerComponent::SetReady(APlayerController* ReadyPlayer)
{
	ServerSetReady(ReadyPlayer);
}

void UPlayerReadyTrackerComponent::ServerSetReady_Implementation(APlayerController* ReadyPlayer)
{
	check(Players.Contains(ReadyPlayer));

	Players[TWeakObjectPtr<APlayerController>{ ReadyPlayer }] = true;
	
	bool AllPlayersReady = true;
	for (const auto& EachPair : Players)
	{
		if (EachPair.Key.IsValid() && EachPair.Value == false)
		{
			AllPlayersReady = false;
			break;
		}
	}

	MulticastOnPlayerReady(ReadyPlayer->PlayerState);

	if (AllPlayersReady)
	{
		MulticastOnAllPlayersReady();
		Players.Empty();
	}
}

void UPlayerReadyTrackerComponent::MulticastOnPlayerReady_Implementation(APlayerState* ReadyPlayer)
{
	OnPlayerReady.Broadcast(ReadyPlayer);
}

void UPlayerReadyTrackerComponent::MulticastOnAllPlayersReady_Implementation()
{
	OnAllPlayersReady.Broadcast();
}
