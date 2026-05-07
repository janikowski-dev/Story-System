#pragma once

#include "MovieSceneSection.h"
#include "Channels/MovieSceneObjectPathChannel.h"
#include "UChronicle_AnimationSection.generated.h"

UCLASS()
class UChronicle_AnimationSection : public UMovieSceneSection
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FMovieSceneObjectPathChannel AnimationChannel;
};