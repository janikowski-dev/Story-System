#include "UChronicle_EmotionSettings.h"

FName UChronicle_EmotionSettings::GetCategoryName() const
{
	return TEXT("Chronicle");
}

TArray<FChronicle_EmotionData> UChronicle_EmotionSettings::GetAllEmotions() const
{
	return Emotions;
}

FChronicle_EmotionData UChronicle_EmotionSettings::GetEmotion(const FGuid Id) const
{
	for (const FChronicle_EmotionData& Emotion : Emotions)
	{
		if (Id != Emotion.Id)
		{
			continue;
		}
		
		return Emotion;
	}

	return {};
}

FString UChronicle_EmotionSettings::GetName(const FGuid Id) const
{
	for (const FChronicle_EmotionData& Emotion : Emotions)
	{
		if (Id != Emotion.Id)
		{
			continue;
		}
		
		return Emotion.Name;
	}

	return {};
}
