// Fill out your copyright notice in the Description page of Project Settings.


#include "SongQuizPlayerState.h"
#include "Net/UnrealNetwork.h"

bool ASongQuizPlayerState::IsHost() const
{
	return bHost;
}

void ASongQuizPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, bHost);
}
