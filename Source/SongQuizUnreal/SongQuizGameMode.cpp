// Copyright Epic Games, Inc. All Rights Reserved.


#include "SongQuizGameMode.h"
#include "SongQuizPlayerController.h"

ASongQuizGameMode::ASongQuizGameMode()
{
	PlayerControllerClass = ASongQuizPlayerController::StaticClass();
}
