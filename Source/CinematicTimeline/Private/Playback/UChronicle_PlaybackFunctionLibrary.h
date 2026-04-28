#pragma once

#include "LevelSequenceActor.h"
#include "UChronicle_PlaybackFunctionLibrary.generated.h"

UCLASS()
class CINEMATICTIMELINE_API UChronicle_PlaybackFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Chronicle|Runtime")
	static void OffsetSpawnableTransforms(
		ALevelSequenceActor* LevelSequenceActor,
		const FVector& LocationOffset,
		const FRotator& RotationOffset
	);
	
	UFUNCTION(BlueprintCallable, Category="Chronicle|Cinematics")
	static void OffsetCamera(
		const ALevelSequenceActor* LevelSequenceActor,
		const FTransform& OwnerTransform,
		const FTransform& ResponseTransform,
		const float VerticalOffset,
		const float ForwardOffset
	);
	
	UFUNCTION(BlueprintCallable, Category = "Chronicle|Runtime")
	static void SetPlaybackPosition(
		ALevelSequenceActor* LevelSequenceActor,
		FFrameNumber StartFrame
	);
};
