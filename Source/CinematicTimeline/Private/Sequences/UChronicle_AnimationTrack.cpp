#include "Sequences/UChronicle_AnimationTrack.h"

#include "MovieSceneSection.h"
#include "Sequences/UChronicle_AnimationSection.h"

UMovieSceneSection* UChronicle_AnimationTrack::CreateNewSection()
{
	return NewObject<UChronicle_AnimationSection>(this, NAME_None, RF_Transactional);
}

void UChronicle_AnimationTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}

bool UChronicle_AnimationTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UChronicle_AnimationSection::StaticClass();
}

bool UChronicle_AnimationTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}

bool UChronicle_AnimationTrack::IsEmpty() const
{
	return Sections.IsEmpty();
}

void UChronicle_AnimationTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UChronicle_AnimationTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

const TArray<UMovieSceneSection*>& UChronicle_AnimationTrack::GetAllSections() const
{
	return Sections;
}