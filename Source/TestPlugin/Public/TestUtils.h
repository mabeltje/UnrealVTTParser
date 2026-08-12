#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TestUtils.generated.h"

UCLASS()
class TESTPLUGIN_API UMyTestClass : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Editor Tools")
	static void PrintHelloEditor(const FString& Message);
};