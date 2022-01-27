// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SynthComponent.h"
#include "TestSynthComponent.generated.h"


UCLASS()
class UFfmpegInitiator : public UObject
{
	GENERATED_BODY()

public:
	virtual void BeginDestroy() override;

	void Initiate(const FString& YoutubeUrl, FSimpleDelegate OnInitiated);
	TArray<float> ReadFloats(int32 FloatCount);

private:
	void* YoutubeDlWritePipe;
	void* YoutubeDlReadPipe;
	void* FfmpegWritePipe;
	void* FfmpegReadPipe;

	FSimpleDelegate InitiationCallback;

	TArray<uint8> ReadBytes;
	int32 NextReadByteIndex = 0;
};


UCLASS(ClassGroup = Synth, meta = (BlueprintSpawnableComponent))
class SONGQUIZUNREAL_API UTestSynthComponent : public USynthComponent
{
	GENERATED_BODY()
	
	// Called when synth is created
	virtual bool Init(int32& SampleRate) override;

	// Called to generate more audio
	virtual int32 OnGenerateAudio(float* OutAudio, int32 NumSamples) override;

private:
	UPROPERTY()
	UFfmpegInitiator* FfmpegInitiator;

	bool bGenerateAudio = false;
};