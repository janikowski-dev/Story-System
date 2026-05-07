#include "FChronicle_EmotionDirectory.h"

#include "UChronicle_EmotionSettings.h"

FChronicle_EmotionSet FChronicle_EmotionDirectory::AllEmotionSet;

FChronicle_EmotionSet& FChronicle_EmotionDirectory::GetAll()
{
	return AllEmotionSet;
}

void FChronicle_EmotionDirectory::Refresh()
{
	const UChronicle_EmotionSettings* const Settings = GetDefault<UChronicle_EmotionSettings>();
	AllEmotionSet.Refresh(Settings->Emotions);
}
