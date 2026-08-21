#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MovieScene.h"
#include "LevelSequence.h"
#include "VTTParser.generated.h"


// Represents a single parsed entry from a .vtt file 
USTRUCT(BlueprintType)
struct FVTTEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VTT")
	float StartTimeSeconds = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VTT")
	float EndTimeSeconds = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VTT")
	FString Text = "";

	UPROPERTY(BlueprintReadWrite, Category = "VTT")
	FFrameNumber StartFrame;

	UPROPERTY(BlueprintReadWrite, Category = "VTT")
	FFrameNumber EndFrame;
};

UCLASS()
class UNREALVTTPARSER_API UVTTParser : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Parses a .vtt file path into an array of FVTTMarker structs
	UFUNCTION(BlueprintCallable, Category = "VTT Processing")
	static bool ParseVTTFile(const FString& FilePath, TArray<FVTTEntry>& OutMarkers);

	// Converts a timestamp into a frame number based on the given frame rate
	UFUNCTION(BlueprintCallable, Category = "VTT Processing")
	static FFrameNumber GetFrameFromSeconds(const FFrameRate FrameRate, float Seconds);

	// Updates the frame numbers for a VTT entry based on the given frame rate
	UFUNCTION(BlueprintCallable, Category = "VTT Processing")
	static void UpdateVTTEntryFrames(UPARAM(ref) FVTTEntry& Entry, const FFrameRate FrameRate);

	UFUNCTION(BlueprintCallable, Category = "VTT Processing")
    static TArray<FMovieSceneMarkedFrame> AddVTTEntryMarkers(ULevelSequence* Sequence, const FFrameNumber StartFrame, const FFrameNumber EndFrame, const FString& GlossLabel);

private:
	static float ConvertVTTTimestampToSeconds(const FString& Timestamp);
};