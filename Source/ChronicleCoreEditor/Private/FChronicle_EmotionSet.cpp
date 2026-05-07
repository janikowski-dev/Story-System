#include "FChronicle_EmotionSet.h"

void FChronicle_EmotionSet::Refresh(const TArray<FChronicle_EmotionData>& Emotions)
{
	for (const FChronicle_EmotionData& Emotion : Emotions)
	{
		const bool bContainsId = Ids.ContainsByPredicate([&](const TSharedPtr<FGuid>& Id)
		{
			return *Id == Emotion.Id;
		});
		
		if (bContainsId)
		{
			NamesById[Emotion.Id] = Emotion.Name;
		}
		else
		{
			TSharedPtr<FGuid> SharedId = MakeShared<FGuid>(Emotion.Id);
			NamesById.Add(Emotion.Id, Emotion.Name);
			Ids.Add(SharedId);
		}
	}
}

TArray<TSharedPtr<FGuid>> FChronicle_EmotionSet::GetSharedIds() const
{
	return Ids;
}

FString FChronicle_EmotionSet::GetName(FGuid Id) const
{
	if (FString const* Found = NamesById.Find(Id))
	{
		return *Found;
	}

	return TEXT("");
}

bool FChronicle_EmotionSet::IsValid(FGuid Id) const
{
	for (const TSharedPtr<FGuid>& IdPointer : Ids)
	{
		if (IdPointer.IsValid() && *IdPointer == Id)
		{
			return true;
		}
	}
	return false;
}
