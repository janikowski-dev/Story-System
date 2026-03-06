#pragma once

#include "FChronicle_SequenceData.h"
#include "UChronicle_CinematicData.generated.h"

UCLASS(BlueprintType, Blueprintable)
class UChronicle_CinematicData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere)
	TMap<FGuid, TSoftObjectPtr<USoundBase>> SoundsByLine;
	
	UPROPERTY(VisibleAnywhere)
	TArray<FChronicle_SequenceData> SequencesData;

	UPROPERTY(VisibleAnywhere)
	TArray<FGuid> LineNodeIds;
};
