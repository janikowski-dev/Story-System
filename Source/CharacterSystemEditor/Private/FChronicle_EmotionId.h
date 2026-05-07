#pragma once

#include "FChronicle_EmotionId.generated.h"

USTRUCT(BlueprintType)
struct CHARACTERSYSTEMEDITOR_API FChronicle_EmotionId
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGuid Id;
};