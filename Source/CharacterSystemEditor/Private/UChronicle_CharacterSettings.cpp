#include "UChronicle_CharacterSettings.h"

FName UChronicle_CharacterSettings::GetCategoryName() const
{
	return TEXT("Chronicle");
}

FName UChronicle_CharacterSettings::GetName(const FGuid Id) const
{
	for (const FChronicle_Character& Character : NonPlayableCharacters)
	{
		if (Character.Id == Id)
		{
			return Character.Name;
		}
	}
	
	for (const FChronicle_Character& Character : PlayableCharacters)
	{
		if (Character.Id == Id)
		{
			return Character.Name;
		}
	}

	return TEXT("");
}
