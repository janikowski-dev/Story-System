#pragma once

#include "FChronicle_EmotionData.generated.h"

USTRUCT(BlueprintType)
struct FChronicle_EmotionData
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGuid Id = FGuid::NewGuid();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
};
