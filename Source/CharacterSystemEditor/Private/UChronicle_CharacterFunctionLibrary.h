#pragma once

#include "UChronicle_CharacterFunctionLibrary.generated.h"

UCLASS()
class CHARACTERSYSTEMEDITOR_API UChronicle_CharacterFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Chronicle|Characters")
	static FName GetName(const FGuid Id);
};