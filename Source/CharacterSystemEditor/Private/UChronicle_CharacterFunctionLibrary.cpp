#include "UChronicle_CharacterFunctionLibrary.h"

#include "UChronicle_CharacterSettings.h"

FName UChronicle_CharacterFunctionLibrary::GetName(const FGuid Id)
{
	return GetDefault<UChronicle_CharacterSettings>()->GetName(Id);
}
