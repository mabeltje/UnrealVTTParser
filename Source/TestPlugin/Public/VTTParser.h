#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VTTParser.generated.h"

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
};

UCLASS()
class TESTPLUGIN_API UVTTParser : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Parses a .vtt file path into an array of FVTTMarker structs
	UFUNCTION(BlueprintCallable, Category = "VTT Processing")
	static bool ParseVTTFile(const FString& FilePath, TArray<FVTTEntry>& OutMarkers);

private:
	static float ConvertVTTTimestampToSeconds(const FString& Timestamp);
};