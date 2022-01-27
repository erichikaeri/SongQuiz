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
	bool IsHost() const;
	
private:
	UPROPERTY(Replicated)
	bool bHost;
};
