#pragma once

#include "LevelSequence.h"
#include "FChronicle_DialogueNodeData.h"
#include "FChronicle_SequenceData.generated.h"

USTRUCT()
struct FChronicle_SequenceData
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere)
	TArray<FChronicle_DialogueNodeData> Nodes;
	
	UPROPERTY(VisibleAnywhere)
	TSoftObjectPtr<ULevelSequence> Sequence;
};