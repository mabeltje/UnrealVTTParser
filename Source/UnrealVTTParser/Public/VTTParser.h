#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MovieSceneSection.h"
#include "VTTParser.generated.h"

class UMovieSceneSkeletalAnimationSection; // Forward declaration

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

USTRUCT(BlueprintType)
struct FSectionLabelEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VTT")
	TObjectPtr<UMovieSceneSection> Section = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VTT")
	FString Label;
};

UCLASS()
class UNREALVTTPARSER_API UVTTParser : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Parses a .vtt file path into an array of FVTTMarker structs
	UFUNCTION(BlueprintCallable, Category = "VTT Processing")
	static bool ParseVTTFile(const FString& FilePath, TArray<FVTTEntry>& OutMarkers);

	UFUNCTION(BlueprintCallable, Category = "VTT Processing")
	static FFrameNumber GetFrameFromSeconds(const FFrameRate FrameRate, float Seconds);

	/** Pairs sections with corresponding labels into a list of structs */
	UFUNCTION(BlueprintCallable, Category = "VTT Processing")
	static FSectionLabelEntry CreateSectionLabelEntry(
		UMovieSceneSection* Section,
		const FString& Label
	);

	UFUNCTION(BlueprintCallable, Category = "VTT Processing")
	static void SetAnimationAsset(
		UMovieSceneSkeletalAnimationSection* Section,
		UAnimSequenceBase* Animation
	);

private:
	static float ConvertVTTTimestampToSeconds(const FString& Timestamp);
};