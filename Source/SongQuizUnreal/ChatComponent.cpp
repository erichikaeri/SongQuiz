// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatComponent.h"

void UChatComponent::Chat(APlayerController* From, const FString& Message)
{
	ServerChat(From, Message);
}

void UChatComponent::ServerChat_Implementation(APlayerController* From, const FString& Message)
{
	MulticastOnChat(From->PlayerState, Message);
}

void UChatComponent::MulticastOnChat_Implementation(APlayerState* From, const FString& Message)
{
	OnChat.Broadcast(From, Message);
}
