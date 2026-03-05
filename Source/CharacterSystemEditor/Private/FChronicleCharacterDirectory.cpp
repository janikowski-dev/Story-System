#include "FChronicleCharacterDirectory.h"

#include "FChronicle_CombinedCharacterSet.h"
#include "UChronicleCharacterSettings.h"

FChronicle_CombinedCharacterSet FChronicleCharacterDirectory::AllCharacterSet(
	PlayableCharacterSet,
	NonPlayableCharacterSet
);
FCharacterSet FChronicleCharacterDirectory::NonPlayableCharacterSet;
FCharacterSet FChronicleCharacterDirectory::PlayableCharacterSet;

FChronicle_CombinedCharacterSet& FChronicleCharacterDirectory::GetAll()
{
	return AllCharacterSet;
}

FCharacterSet& FChronicleCharacterDirectory::GetPlayable()
{
	return PlayableCharacterSet;
}

FCharacterSet& FChronicleCharacterDirectory::GetNonPlayable()
{
	return NonPlayableCharacterSet;
}

void FChronicleCharacterDirectory::Refresh()
{
	const UChronicleCharacterSettings* const Settings = GetDefault<UChronicleCharacterSettings>();
	NonPlayableCharacterSet.Refresh(Settings->NonPlayableCharacters);
	PlayableCharacterSet.Refresh(Settings->PlayableCharacters);
}
