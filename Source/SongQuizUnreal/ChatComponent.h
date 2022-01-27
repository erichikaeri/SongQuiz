// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ChatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SONGQUIZUNREAL_API UChatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnChat, APlayerState*, const FString& Message);
	FOnChat OnChat;

	void Chat(APlayerController* From, const FString& Message);

private:
	UFUNCTION(Server, Reliable)
	void ServerChat(APlayerController* From, const FString& Message);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnChat(APlayerState* From, const FString& Message);
};
