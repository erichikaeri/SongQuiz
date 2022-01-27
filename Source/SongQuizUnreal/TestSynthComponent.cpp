// Fill out your copyright notice in the Description page of Project Settings.


#include "TestSynthComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Async/Async.h"


void UFfmpegInitiator::BeginDestroy()
{
	Super::BeginDestroy();

	FPlatformProcess::ClosePipe(YoutubeDlReadPipe, YoutubeDlWritePipe);
	FPlatformProcess::ClosePipe(FfmpegReadPipe, FfmpegWritePipe);
}

void UFfmpegInitiator::Initiate(const FString& YoutubeUrl, FSimpleDelegate OnInitiated)
{
	const FString ProjDir = UKismetSystemLibrary::GetProjectDirectory();
	const FString YoutubeDlPath = FPaths::Combine(ProjDir, TEXT("youtube-dl.exe"));
	const FString FfmpegPath = FPaths::Combine(ProjDir, TEXT("ffmpeg.exe"));

	InitiationCallback = OnInitiated;

	FPlatformProcess::CreatePipe(YoutubeDlReadPipe, YoutubeDlWritePipe);
	FPlatformProcess::CreatePipe(FfmpegReadPipe, FfmpegWritePipe);

	TWeakObjectPtr<ThisClass> WeakThis = this;

	AsyncTask(ENamedThreads::AnyHiPriThreadHiPriTask, [this, WeakThis, YoutubeDlPath, FfmpegPath, YoutubeUrl]()
	{
		if (!WeakThis.IsValid())
		{
			return;
		}

		FProcHandle Handle = FPlatformProcess::CreateProc
		(
			*YoutubeDlPath, 
			*FString::Printf(TEXT("\"%s\" -g"), *YoutubeUrl), 
			true, 
			false, 
			false, 
			nullptr, 
			0, 
			nullptr, 
			YoutubeDlWritePipe
		);

		FPlatformProcess::WaitForProc(Handle);

		const FString YoutubeDlOutput = FPlatformProcess::ReadPipe(YoutubeDlReadPipe);

		FString StreamUrl;
		YoutubeDlOutput.Split("\n", nullptr, &StreamUrl);
		StreamUrl.TrimStartAndEndInline();

		FPlatformProcess::CreateProc
		(
			*FfmpegPath, 
			*FString::Printf(TEXT("-i \"%s\" -f f32le -acodec pcm_f32le -loglevel quiet -ac 2 -ar 44100 -"), *StreamUrl), 
			true, 
			false, 
			false, 
			nullptr, 
			0, 
			nullptr, 
			FfmpegWritePipe
		);

		AsyncTask(ENamedThreads::GameThread, [this, WeakThis]()
		{
			if (!WeakThis.IsValid())
			{
				return;
			}

			InitiationCallback.ExecuteIfBound();
		});
	});
}

TArray<float> UFfmpegInitiator::ReadFloats(int32 FloatCount)
{
	TArray<uint8> MoreBytes;
	FPlatformProcess::ReadPipeToArray(FfmpegReadPipe, MoreBytes);
	ReadBytes.Append(MoreBytes);

	const int32 AvailableFloatCount = (ReadBytes.Num() - NextReadByteIndex) / 4;
	if (AvailableFloatCount < FloatCount)
	{
		return {};
	}

	TArray<float> Ret;
	for (int32 i = NextReadByteIndex; i < NextReadByteIndex + FloatCount * 4; i += 4)
	{
		uint32 PreFloat = ReadBytes[i];
		PreFloat |= ReadBytes[i + 1] << 8;
		PreFloat |= ReadBytes[i + 2] << 16;
		PreFloat |= ReadBytes[i + 3] << 24;

		Ret.Add(*reinterpret_cast<float*>(&PreFloat));
	}

	NextReadByteIndex += FloatCount * 4;

	if (ReadBytes.Num() > 10000000)
	{
		TArray<uint8> TrimmedReadBytes(&ReadBytes[NextReadByteIndex], ReadBytes.Num() - NextReadByteIndex);
		ReadBytes = MoveTemp(TrimmedReadBytes);
		NextReadByteIndex = 0;
	}

	return Ret;
}

bool UTestSynthComponent::Init(int32& SampleRate)
{
	SampleRate = 44100;
	NumChannels = 2;

	FfmpegInitiator = NewObject<UFfmpegInitiator>(this);
	FfmpegInitiator->Initiate(TEXT("https://youtu.be/35WteJ60cps"), FSimpleDelegate::CreateWeakLambda(this, [this]()
	{
		bGenerateAudio = true;
	}));

	return true;
}

int32 UTestSynthComponent::OnGenerateAudio(float* OutAudio, int32 NumSamples)
{
	if (!bGenerateAudio)
	{
		return 0;
	}

	int32 WriteIndex = 0;
	for (float Each : FfmpegInitiator->ReadFloats(NumSamples))
	{
		OutAudio[WriteIndex] = Each;
		WriteIndex++;
	}
	
	return WriteIndex;
}
