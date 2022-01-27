// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerReadyTrackerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SONGQUIZUNREAL_API UPlayerReadyTrackerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerReady, APlayerState*);
	FOnPlayerReady OnPlayerReady;

	FSimpleMulticastDelegate OnAllPlayersReady;

	void SetPlayersToWaitFor(const TArray<APlayerController*>& PlayerList);
	void SetReady(APlayerController* ReadyPlayer);

private:
	UFUNCTION(Server, Reliable)
	void ServerSetReady(APlayerController* ReadyPlayer);
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnPlayerReady(APlayerState* ReadyPlayer);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnAllPlayersReady();

	TMap<TWeakObjectPtr<APlayerController>, bool> Players;
};
