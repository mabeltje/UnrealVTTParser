# UnrealVTTParser

An Unreal Engine plugin for parsing VTT subtitle files and integrating them with the Sequencer and Movie Scene system.


## Overview

UnrealVTTParser provides a Blueprint-callable API for working with VTT subtitle files in Unreal Engine. Parse subtitle data, convert timestamps to frame numbers, and map entries to Sequencer sections without directly interacting with low-level parsing logic.


## API Overview

| Category | Function | Description |
| :--- | :--- | :--- |
| **Parsing** | `ParseVTTFile(const FString& FilePath, TArray<FVTTEntry>& OutMarkers)` | Parses a `.vtt` file path into an array of `FVTTEntry` structs. Returns `true` if parsing succeeded. |
| **Conversion** | `GetFrameFromSeconds(const FFrameRate FrameRate, float Seconds)` | Converts a time value in seconds to an `FFrameNumber` based on the given frame rate. |
| **Sequencer** | `CreateSectionLabelEntry(UMovieSceneSection* Section, const FString& Label)` | Pairs a Movie Scene section with a string label into an `FSectionLabelEntry` struct. |
| **Sequencer** | `SetAnimationAsset(UMovieSceneSkeletalAnimationSection* Section, UAnimSequenceBase* Animation)` | Sets an animation sequence asset on a skeletal animation section. |


## Data Structures

### `FVTTEntry`

Represents a single subtitle entry containing timing (in seconds and frame numbers) and raw subtitle text.

```cpp
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
```

### `FSectionLabelEntry`

Pairs a Movie Scene section with a string label for easy identification in Sequencer.

```cpp
USTRUCT(BlueprintType)
struct FSectionLabelEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VTT")
    TObjectPtr<UMovieSceneSection> Section = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VTT")
    FString Label;
};
```

## Installation

1. Place the `UnrealVTTParser` folder in your project's `Plugins/` directory.
2. Regenerate Visual Studio project files.
3. Rebuild the project.
4. Enable the plugin in Unreal Editor: **Edit > Plugins** → Search for **UnrealVTTParser** → Check **Enable**.

