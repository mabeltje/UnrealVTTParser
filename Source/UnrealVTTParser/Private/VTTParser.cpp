#include "VTTParser.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "HAL/FileManager.h"
#include "Framework/Application/SlateApplication.h"
#include "Sections/MovieSceneSkeletalAnimationSection.h"

void UVTTParser::SetAnimationAsset(
	UMovieSceneSkeletalAnimationSection* Section,
	UAnimSequenceBase* Animation)
{
	if (!Section || !Animation)
	{
		return;
	}

	Section->Params.Animation = Animation;
	Section->Modify(true);

	return;
}

FSectionLabelEntry UVTTParser::CreateSectionLabelEntry(
	UMovieSceneSection* Section,
	const FString& Label)
{
	FSectionLabelEntry Entry;

	Entry.Section = Section;
	Entry.Label = Label;

	return Entry;
}

float UVTTParser::ConvertVTTTimestampToSeconds(const FString& Timestamp)
{
	TArray<FString> Parts;
	Timestamp.TrimStartAndEnd().ParseIntoArray(Parts, TEXT(":"), true);

	float Hours = 0.0f;
	float Minutes = 0.0f;
	float Seconds = 0.0f;

	if (Parts.Num() == 3)
	{
		Hours = FCString::Atof(*Parts[0]);
		Minutes = FCString::Atof(*Parts[1]);
		Seconds = FCString::Atof(*Parts[2]);
	}
	else if (Parts.Num() == 2)
	{
		Minutes = FCString::Atof(*Parts[0]);
		Seconds = FCString::Atof(*Parts[1]);
	}

	return (Hours * 3600.0f) + (Minutes * 60.0f) + Seconds;
}

FFrameNumber UVTTParser::GetFrameFromSeconds(const FFrameRate FrameRate, float Seconds)
{
	return FrameRate.AsFrameTime(Seconds).RoundToFrame();
}

bool UVTTParser::ParseVTTFile(const FString& FilePath, TArray<FVTTEntry>& OutEntries)
{
	OutEntries.Empty();

	FString FileContent;
	if (!FFileHelper::LoadFileToString(FileContent, *FilePath))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load VTT file: %s"), *FilePath);
		return false;
	}

	// Normalize line endings
	FileContent = FileContent.Replace(TEXT("\r\n"), TEXT("\n"));
	TArray<FString> Lines;
	FileContent.ParseIntoArrayLines(Lines);

	for (int32 i = 0; i < Lines.Num(); ++i)
	{
		FString CurrentLine = Lines[i].TrimStartAndEnd();

		// Find timestamp lines containing "-->"
		if (CurrentLine.Contains(TEXT("-->")))
		{
			FString StartStr, EndStr;
			if (CurrentLine.Split(TEXT("-->"), &StartStr, &EndStr))
			{
				FVTTEntry Marker;
				Marker.StartTimeSeconds = ConvertVTTTimestampToSeconds(StartStr);
				
				// Strip optional cue settings (e.g. align:start) if present
				FString CleanEndStr = EndStr.TrimStartAndEnd();
				int32 SpaceIndex;
				if (CleanEndStr.FindChar(' ', SpaceIndex))
				{
					CleanEndStr = CleanEndStr.Left(SpaceIndex);
				}
				Marker.EndTimeSeconds = ConvertVTTTimestampToSeconds(CleanEndStr);

				// Read payload text lines directly following the timestamp
				int32 TextLineIdx = i + 1;
				while (TextLineIdx < Lines.Num())
				{
					FString TextLine = Lines[TextLineIdx].TrimStartAndEnd();

					// Stop reading if we hit an empty line or the start of a new cue block
					if (TextLine.IsEmpty() || TextLine.Contains(TEXT("-->")))
					{
						break;
					}

					// Skip standalone numeric Cue IDs if they appear right before a timestamp on the next line
					if (TextLine.IsNumeric() && (TextLineIdx + 1 < Lines.Num()) && Lines[TextLineIdx + 1].Contains(TEXT("-->")))
					{
						break;
					}

					if (!Marker.Text.IsEmpty())
					{
						Marker.Text += "\n";
					}
					Marker.Text += TextLine;
					TextLineIdx++;
				}

				OutEntries.Add(Marker);
			}
		}
	}

	// Sort markers chronologically by StartTimeSeconds (Fixes out-of-order cues like Cue #8)
	OutEntries.Sort([](const FVTTEntry& A, const FVTTEntry& B) {
		return A.StartTimeSeconds < B.StartTimeSeconds;
	});

	return OutEntries.Num() > 0;
}