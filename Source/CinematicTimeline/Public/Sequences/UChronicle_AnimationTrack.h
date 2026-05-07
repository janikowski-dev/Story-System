#pragma once

#include "MovieSceneNameableTrack.h"
#include "UChronicle_AnimationTrack.generated.h"

UCLASS()
class UChronicle_AnimationTrack : public UMovieSceneNameableTrack
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<TObjectPtr<UMovieSceneSection>> Sections;
	
public:
	virtual UMovieSceneSection* CreateNewSection() override;
	virtual void AddSection(UMovieSceneSection& Section) override;
	virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;
	virtual bool HasSection(const UMovieSceneSection& Section) const override;
	virtual bool IsEmpty() const override;
	virtual void RemoveSection(UMovieSceneSection& Section) override;
	virtual void RemoveSectionAt(int32 SectionIndex) override;
	virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;
	virtual FName GetTrackName() const override { return TEXT("Chronicle Animation"); }
};