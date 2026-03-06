#pragma once

#include "UChronicle_DialogueData.h"
#include "Data/UChronicle_CinematicData.h"
#include "UChronicle_CinematicImporterMediator.generated.h"

UCLASS()
class CINEMATICTIMELINEEDITOR_API UChronicle_CinematicImporterMediator : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Chronicle|Dialogue")
	static UChronicle_CinematicData* ConvertToCinematicData(const UChronicle_DialogueData* Asset);
};