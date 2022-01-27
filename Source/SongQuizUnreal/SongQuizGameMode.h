// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SongQuizGameState.h"
#include "GameFramework/GameModeBase.h"
#include "SongQuizGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SONGQUIZUNREAL_API ASongQuizGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASongQuizGameMode();

	void PlayNextSong();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ASongQuizGameState* SongQuizGameState;
};
