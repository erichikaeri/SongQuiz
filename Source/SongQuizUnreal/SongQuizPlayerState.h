// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SongQuizPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SONGQUIZUNREAL_API ASongQuizPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnScoreChanged, ASongQuizPlayerState*, int32);
	FOnScoreChanged OnScoreChanged;

	int32 GetIntScore() const;
	bool IsHost() const;

	void SetIntScore(int32 NewScore);
	
private:
	UPROPERTY(Replicated)
	bool bHost;

	UPROPERTY(ReplicatedUsing=OnRep_IntScore)
	int32 IntScore;

	UFUNCTION()
	void OnRep_IntScore();
};
