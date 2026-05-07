#pragma once
#include "FChronicle_EmotionId.h"

#include "FChronicle_EmotionAnimationEntry.generated.h"

USTRUCT()
struct FChronicle_EmotionAnimationEntry
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FChronicle_EmotionId EmotionId;

	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UAnimSequence>> Sequences;
};