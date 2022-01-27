// Fill out your copyright notice in the Description page of Project Settings.


#include "SongQuizPlayerState.h"
#include "Net/UnrealNetwork.h"

int32 ASongQuizPlayerState::GetIntScore() const
{
	return IntScore;
}

bool ASongQuizPlayerState::IsHost() const
{
	return bHost;
}

void ASongQuizPlayerState::SetIntScore(int32 NewScore)
{
	check(GetNetMode() != NM_Client);

	IntScore = NewScore;
	
	if (GetNetMode() != NM_DedicatedServer)
	{
		OnRep_IntScore();
	}
}

void ASongQuizPlayerState::OnRep_IntScore()
{
	OnScoreChanged.Broadcast(this, IntScore);
}

void ASongQuizPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, bHost);
	DOREPLIFETIME(ThisClass, IntScore);
}
