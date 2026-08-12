#include "TestUtils.h"
#include "Engine/Engine.h"

void UMyTestClass::PrintHelloEditor(const FString& Message)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("EUW C++ Output: %s"), *Message));
	}
	UE_LOG(LogTemp, Warning, TEXT("EUW C++ Executed: %s"), *Message);
}